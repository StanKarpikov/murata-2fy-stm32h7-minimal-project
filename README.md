# Minimal project for STM32H7 and Murata 2FY to run Wi-Fi 6E connection and iperf on both STA and AP

Intended for test and verification purposes, not for production use.

## Useful commands

### Put Interface into Managed Mode

```bash
# See the adapters
sudo iw dev

# Get supported channels and frequencies
sudo iw list
# * 5955.0 MHz [1] (12.0 dBm) (no IR)
# * 5995.0 MHz [9] (12.0 dBm) (no IR)
# * 6695.0 MHz [149] (12.0 dBm) (no IR)
# * 7115.0 MHz [233] (12.0 dBm) (no IR)

sudo iw reg set US

sudo iw dev wlp0s20f0u2i3 del

sudo iw dev wlan2 del
sudo iw phy phy1 interface add wlan2 type monitor
sudo ip link set wlan2 up

# 6 GHz channel 149
sudo iw dev wlan2 set freq 6695 20

# 5 GHz cahnnel 48 
sudo iw dev wlan2 set freq 5240 20

# 5 GHz cahnnel 100 
sudo iw dev wlan2 set freq 5500 20

# 2.4 GHz channel 10
sudo iw dev wlan2 set freq 2457 20

# To check what could use the adapter:
# sudo airmon-ng check
# sudo airmon-ng check kill
```

### Testing using console app

```bash
# On the AP
start_ap "ApTest" wpa3 "12345678" 149 3 20 192.168.2.1 255.255.255.0
iperf -c 192.168.2.2 -l 500 -u -b 500pps -t 2100

# On the STA
wifi_join "ApTest" wpa3 "12345678"
iperf -s -u
```

### Wireshart filter for CTS/RTS:

```
wlan.fc.type_subtype != 0x08 && wlan.fc.type_subtype != 0x0d && (wlan.fc.type_subtype == 0x1b || wlan.fc.type_subtype == 0x1c)
```