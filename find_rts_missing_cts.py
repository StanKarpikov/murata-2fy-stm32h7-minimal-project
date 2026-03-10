#!/usr/bin/env python3
"""
Find WiFi packets with missing responses (RTS/CTS or QoS Data/ACK) in a pcap capture file.

Usage:
    python find_rts_missing_cts.py <capture.pcap[.gz]> [options]

    Modes:
    --mode rts-cts   Find RTS packets without matching CTS responses (default)
    --mode qos-ack   Find QoS Data frames without matching ACK responses

Requirements:
    pip install dpkt tqdm
"""

import argparse
import bisect
import gzip
import os
import struct
import sys

try:
    import dpkt
except ImportError:
    print("Error: dpkt is required.  Install with:  pip install dpkt tqdm")
    sys.exit(1)

try:
    from tqdm import tqdm
except ImportError:
    print("Error: tqdm is required.  Install with:  pip install tqdm")
    sys.exit(1)

# ---------------------------------------------------------------------------
# 802.11 constants
# ---------------------------------------------------------------------------
DOT11_TYPE_CONTROL = 1
DOT11_TYPE_DATA    = 2
DOT11_SUBTYPE_RTS  = 11
DOT11_SUBTYPE_CTS  = 12
DOT11_SUBTYPE_ACK  = 13
DOT11_SUBTYPE_QOS_DATA = 8  # QoS Data frame subtype

DEFAULT_CTS_TIMEOUT = 0.003   # 3 ms =  1 ms — SIFS + CTS propagation budget + 2 ms additional
DEFAULT_ACK_TIMEOUT = 0.003   # 3 ms = SIFS + ACK propagation budget
DEFAULT_MAC_FILTER = "ea:cb:f5:40:7e:7a"  # Default MAC address to filter
DEFAULT_MODE = "rts-cts"     # Default mode: "rts-cts" or "qos-ack"


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def _mac_str(raw: bytes) -> str:
    return ":".join(f"{b:02x}" for b in raw)

def _mac_bytes(mac_str: str) -> bytes:
    """Convert MAC address string to bytes."""
    return bytes.fromhex(mac_str.replace(":", ""))


def _strip_radiotap(buf: bytes, linktype: int) -> bytes | None:
    """Return the raw 802.11 MAC frame, stripping any radio metadata header."""
    if linktype == dpkt.pcap.DLT_IEEE802_11_RADIO:
        if len(buf) < 4:
            return None
        rt_len = struct.unpack_from("<H", buf, 2)[0]
        return buf[rt_len:]
    if linktype == 119:          # DLT_PRISM_HEADER — always 144 bytes
        return buf[144:]
    return buf                   # DLT_IEEE802_11 — already raw


class _TqdmRawWrapper:
    """
    Thin wrapper around a raw file handle that updates a tqdm bar as bytes
    are read.  Used for both plain and gzip files — for gzip the underlying
    raw_fh position reflects compressed bytes consumed, which gives a smooth
    0-100 % progress even though the decompressed size is unknown.
    """
    def __init__(self, raw_fh, progress: tqdm):
        self._raw   = raw_fh
        self._prog  = progress
        self._last  = 0

    def read(self, n=-1):
        data = self._raw.read(n)
        pos  = self._raw.tell()
        self._prog.update(pos - self._last)
        self._last = pos
        return data

    def seek(self, *a):  return self._raw.seek(*a)
    def tell(self):      return self._raw.tell()
    def write(self, *a): return self._raw.write(*a)


# ---------------------------------------------------------------------------
# Core function
# ---------------------------------------------------------------------------

def find_qos_data_without_ack(
    pcap_path: str,
    ack_timeout: float = DEFAULT_ACK_TIMEOUT,
    verbose: bool = False,
    mac_filter: str = DEFAULT_MAC_FILTER,
) -> list[dict]:
    """
    Single-pass stream over a pcap/pcap.gz file to find QoS Data frames without ACKs.

    ACK index structure:
        ack_index: dict[addr2_bytes -> list[float]]
        A sorted list of timestamps per transmitter MAC.
        On each QoS Data frame we bisect into ack_index[qos.addr2] to find any ACK
        that arrived within the timeout window — O(log N) per lookup.

    Returns a list of dicts: {index, timestamp, src, dst}
    """
    print(f"[*] Opening: {pcap_path}")
    is_gz = pcap_path.endswith(".gz")

    try:
        raw_fh = open(pcap_path, "rb")
    except FileNotFoundError:
        print(f"Error: file not found — {pcap_path}")
        sys.exit(1)

    file_size = os.path.getsize(pcap_path)
    progress  = tqdm(
        total=file_size,
        unit="B", unit_scale=True, unit_divisor=1024,
        desc="Scanning", dynamic_ncols=True,
    )

    # Wrap the raw handle so tqdm tracks compressed-byte consumption
    tracked_fh = _TqdmRawWrapper(raw_fh, progress)
    fh = gzip.open(tracked_fh, "rb") if is_gz else tracked_fh

    try:
        pcap = dpkt.pcap.Reader(fh)
    except Exception:
        fh.seek(0)
        try:
            pcap = dpkt.pcapng.Reader(fh)
        except Exception as e:
            progress.close()
            print(f"Error reading capture file: {e}")
            sys.exit(1)

    linktype = pcap.datalink()
    if linktype not in (dpkt.pcap.DLT_IEEE802_11,
                        dpkt.pcap.DLT_IEEE802_11_RADIO,
                        119):
        tqdm.write(f"Warning: unexpected link type {linktype} "
                   "(expected 105/127/119 for 802.11). Proceeding anyway.")

    # ack_index[transmitter_mac_bytes] = sorted list of ACK arrival timestamps
    ack_index: dict[bytes, list[float]] = {}
    pending_qos: list[tuple[int, float, bytes, bytes]] = []   # (idx, ts, src, dst)

    n_qos = n_ack = total = 0
    t0 = None

    # Convert MAC filter to bytes for comparison
    filter_mac = _mac_bytes(mac_filter)

    for idx, (ts, buf) in enumerate(pcap, start=1):
        total = idx

        if t0 is None:
            t0 = ts

        dot11 = _strip_radiotap(buf, linktype)
        if dot11 is None or len(dot11) < 10:
            continue

        fc = struct.unpack_from("<H", dot11, 0)[0]
        frame_type = (fc >> 2) & 0x3
        subtype = (fc >> 4) & 0xF
        addr1   = 0 #dot11[4:10]                        # raw bytes — no string yet

        if frame_type == DOT11_TYPE_CONTROL and subtype == DOT11_SUBTYPE_ACK:
            n_ack += 1
            if addr1 not in ack_index:
                ack_index[addr1] = []
            ack_index[addr1].append(ts)
            if verbose:
                tqdm.write(f"  ACK #{idx:>7}  ts={ts:.6f}  RA={_mac_str(addr1)}")

        elif frame_type == DOT11_TYPE_DATA and subtype == DOT11_SUBTYPE_QOS_DATA:
            if len(dot11) < 24:  # QoS Data frames have additional QoS control field
                continue
            addr2 = dot11[10:16]  # Transmitter address

            # Only process QoS Data packets from the filtered MAC address
            # if addr2 == filter_mac:
            n_qos += 1
            pending_qos.append((idx, ts, addr2, addr1))
            if verbose:
                tqdm.write(f"  QoS #{idx:>7}  ts={ts:.6f}  "
                            f"{_mac_str(addr2)} -> {_mac_str(addr1)}")

    progress.close()
    raw_fh.close()

    print(f"[*] Packets scanned : {total}")
    print(f"[*] QoS Data found  : {n_qos}")
    print(f"[*] ACK found       : {n_ack}")

    # ── Match pending QoS Data against ACK index — O(Q log A) total ─────────
    missing = []
    for (idx, qos_ts, src, dst) in pending_qos:
        ack_times = ack_index.get(0)  # ACKs are sent to the original transmitter (addr2)
        matched   = False
        if ack_times:
            pos = bisect.bisect_left(ack_times, qos_ts)
            if pos < len(ack_times) and ack_times[pos] - qos_ts <= ack_timeout:
                matched = True
        if not matched:
            missing.append({
                "index":     idx,
                "timestamp": qos_ts - t0,
                "src":       _mac_str(src),
                "dst":       0 #_mac_str(dst),
            })

    return missing

def find_rts_without_cts(
    pcap_path: str,
    cts_timeout: float = DEFAULT_CTS_TIMEOUT,
    verbose: bool = False,
    mac_filter: str = DEFAULT_MAC_FILTER,
) -> list[dict]:
    """
    Single-pass stream over a pcap/pcap.gz file.

    CTS index structure:
        cts_index: dict[addr1_bytes -> list[float]]
        A sorted list of timestamps per receiver MAC.
        On each RTS we bisect into cts_index[rts.addr2] to find any CTS
        that arrived within the timeout window — O(log N) per lookup.

    Returns a list of dicts: {index, timestamp, src, dst}
    """
    print(f"[*] Opening: {pcap_path}")
    is_gz = pcap_path.endswith(".gz")

    try:
        raw_fh = open(pcap_path, "rb")
    except FileNotFoundError:
        print(f"Error: file not found — {pcap_path}")
        sys.exit(1)

    file_size = os.path.getsize(pcap_path)
    progress  = tqdm(
        total=file_size,
        unit="B", unit_scale=True, unit_divisor=1024,
        desc="Scanning", dynamic_ncols=True,
    )

    # Wrap the raw handle so tqdm tracks compressed-byte consumption
    tracked_fh = _TqdmRawWrapper(raw_fh, progress)
    fh = gzip.open(tracked_fh, "rb") if is_gz else tracked_fh

    try:
        pcap = dpkt.pcap.Reader(fh)
    except Exception:
        fh.seek(0)
        try:
            pcap = dpkt.pcapng.Reader(fh)
        except Exception as e:
            progress.close()
            print(f"Error reading capture file: {e}")
            sys.exit(1)

    linktype = pcap.datalink()
    if linktype not in (dpkt.pcap.DLT_IEEE802_11,
                        dpkt.pcap.DLT_IEEE802_11_RADIO,
                        119):
        tqdm.write(f"Warning: unexpected link type {linktype} "
                   "(expected 105/127/119 for 802.11). Proceeding anyway.")

    # cts_index[receiver_mac_bytes] = sorted list of CTS arrival timestamps
    cts_index: dict[bytes, list[float]] = {}
    pending_rts: list[tuple[int, float, bytes, bytes]] = []   # (idx, ts, src, dst)

    n_rts = n_cts = total = 0
    t0 = None

    # Convert MAC filter to bytes for comparison
    filter_mac = _mac_bytes(mac_filter)

    for idx, (ts, buf) in enumerate(pcap, start=1):
        total = idx

        if t0 is None:
            t0 = ts

        dot11 = _strip_radiotap(buf, linktype)
        if dot11 is None or len(dot11) < 10:
            continue

        fc = struct.unpack_from("<H", dot11, 0)[0]
        if (fc >> 2) & 0x3 != DOT11_TYPE_CONTROL:   # fast-skip non-control
            continue

        subtype = (fc >> 4) & 0xF
        addr1   = dot11[4:10]                        # raw bytes — no string yet

        if subtype == DOT11_SUBTYPE_CTS:
            n_cts += 1
            if addr1 not in cts_index:
                cts_index[addr1] = []
            cts_index[addr1].append(ts)
            if verbose:
                tqdm.write(f"  CTS #{idx:>7}  ts={ts:.6f}  RA={_mac_str(addr1)}")

        elif subtype == DOT11_SUBTYPE_RTS:
            if len(dot11) < 16:
                continue
            addr2 = dot11[10:16]

            # Only process RTS packets from the filtered MAC address
            # if addr2 == filter_mac:
            n_rts += 1
            pending_rts.append((idx, ts, addr2, addr1))
            if verbose:
                tqdm.write(f"  RTS #{idx:>7}  ts={ts:.6f}  "
                            f"{_mac_str(addr2)} -> {_mac_str(addr1)}")

    progress.close()
    raw_fh.close()

    print(f"[*] Packets scanned : {total}")
    print(f"[*] RTS found       : {n_rts}")
    print(f"[*] CTS found       : {n_cts}")

    # ── Match pending RTS against CTS index — O(R log C) total ───────────────
    missing = []
    for (idx, rts_ts, src, dst) in pending_rts:
        cts_times = cts_index.get(src)
        matched   = False
        if cts_times:
            pos = bisect.bisect_left(cts_times, rts_ts)
            if pos < len(cts_times) and cts_times[pos] - rts_ts <= cts_timeout:
                matched = True
        if not matched:
            missing.append({
                "index":     idx,
                "timestamp": rts_ts - t0,
                "src":       _mac_str(src),
                "dst":       _mac_str(dst),
            })

    return missing


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(
        description="Find WiFi packets with missing responses (RTS/CTS or QoS Data/ACK)."
    )
    parser.add_argument("pcap_file",
                        help="Path to .pcap, .pcapng, .pcap.gz, or .pcapng.gz")
    parser.add_argument("--mode", choices=["rts-cts", "qos-ack"], default=DEFAULT_MODE,
                        help=f"Analysis mode: 'rts-cts' for RTS/CTS or 'qos-ack' for QoS Data/ACK (default {DEFAULT_MODE})")
    parser.add_argument("--timeout", type=float, default=DEFAULT_CTS_TIMEOUT,
                        metavar="SECS",
                        help=f"Response wait window in seconds (default depends on mode)")
    parser.add_argument("--verbose", "-v", action="store_true")
    parser.add_argument("--output", "-o", metavar="FILE")
    parser.add_argument("--min-gap-length", type=int, default=6,
                        metavar="N",
                        help="Minimum number of consecutive packets in a gap to include (default 6)")
    parser.add_argument("--mac-filter", type=str, default=DEFAULT_MAC_FILTER,
                        metavar="MAC",
                        help=f"Only process packets from this MAC address (default {DEFAULT_MAC_FILTER})")
    args = parser.parse_args()

    # Determine which function to use based on mode
    if args.mode == "qos-ack":
        # For QoS Data/ACK mode, use the ACK timeout
        missing = find_qos_data_without_ack(args.pcap_file, args.timeout, args.verbose, args.mac_filter)
        packet_type = "QoS Data"
        response_type = "ACK"
    else:
        # Default to RTS/CTS mode
        missing = find_rts_without_cts(args.pcap_file, args.timeout, args.verbose, args.mac_filter)
        packet_type = "RTS"
        response_type = "CTS"

    # Split missing RTS in groups. Intervals between groups are 15 ms or more
    GAP = 0.015  # 15 ms
    gaps, current = [], []
    last_gap_end = 0.0

    for i, e in enumerate(missing):
        if i == 0 or e["timestamp"] - missing[i-1]["timestamp"] > GAP:
            if current:
                gaps.append(current)
                last_gap_end = current[-1]["timestamp"]
            current = [e]
        else:
            current.append(e)
    if current:
        gaps.append(current)

    # Only keep large groups
    filtered_gaps = [gap for gap in gaps if len(gap) >= args.min_gap_length]

    print()
    print("=" * 66)
    print(f"  {packet_type} packets WITHOUT a matching {response_type}: {len(missing)}")
    print("=" * 66)

    print(f"{'Pkt Index':<11}  {'Timestamp (s)':<20} ")
    print("-" * 30)

    lines = []
    if filtered_gaps:
        for gap_idx, gap in enumerate(filtered_gaps, 1):
            gap_start = gap[0]["timestamp"]
            time_since_last = gap_start - last_gap_end if gap_idx > 1 else 0.0

            gap_duration = gap[-1]["timestamp"] - gap[0]["timestamp"]
            lines.append(f"\nGap {gap_idx}, Time since last gap: {time_since_last:.3f} seconds. Duration {gap_duration*1000:.0f} ms")

            # Print only first and last packet in gap
            for i, e in enumerate([gap[0], gap[-1]], 1):
                lines.append(
                    f"{e['index']:<11}  {e['timestamp']:<20.6f}  "
                )

            last_gap_end = gap[0]["timestamp"]
    else:
        lines.append(f"  Every {packet_type} received a {response_type} within the timeout window.")

    print("\n".join(lines))

    if args.output:
        with open(args.output, "w") as f:
            f.write("\n".join(lines) + "\n")
        print(f"\n[*] Results saved to: {args.output}")

    return 1 if missing else 0


if __name__ == "__main__":
    sys.exit(main())
