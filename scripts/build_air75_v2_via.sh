#!/usr/bin/env bash
set -euo pipefail

# Prefer the ARM GCC toolchain that includes newlib headers,
# and ensure binutils (arm-none-eabi-ar) is on PATH.
export PATH="/opt/homebrew/opt/arm-none-eabi-gcc@8/bin:/opt/homebrew/opt/arm-none-eabi-binutils/bin:${PATH}"

qmk compile -kb nuphy/air75_v2/ansi -km via
