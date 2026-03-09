#!/bin/bash

set -x

# Script to program QSPI flash using STM32_Programmer_CLI with external loader
# Converts ELF to BIN and handles multiple section programming

ELF_FILE="${1:-build/Debug/stm32h7_cubemx.elf}"
SERIAL_NUMBER="$2"
PROGRAMMER="$HOME/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI"
EXT_LOADER="$HOME/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/ExternalLoader/H750_QSPI_MA.stldr"

if [ -z "$SERIAL_NUMBER" ]; then
    echo "Error: Serial number not provided"
    echo "Usage: $0 <elf_file> <serial_number>"
    exit 1
fi

"$PROGRAMMER" -c port=swd sn="$SERIAL_NUMBER" --vb 2 --extload "$EXT_LOADER" --download "$ELF_FILE"
