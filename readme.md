# NuPhy Air75 V2 (VIA) + Achordion Build Notes

This keymap adds Achordion to the stock VIA firmware without changing the key layout.
It is set up for the NuPhy fork of QMK on branch `nuphy-keyboards`.

## Why the non-module Achordion install
The Achordion community-module flow ("modules" in `keymap.json`) is not wired up in this NuPhy fork.
Using the non-module install (local `achordion.c`/`achordion.h` in the keymap folder) is the reliable path here.

## Files added or changed
- `keyboards/nuphy/air75_v2/ansi/keymaps/via/achordion.c`
- `keyboards/nuphy/air75_v2/ansi/keymaps/via/achordion.h`
- `keyboards/nuphy/air75_v2/ansi/keymaps/via/keymap.c` (hooks `process_achordion()` and `achordion_task()`)
- `keyboards/nuphy/air75_v2/ansi/keymaps/via/rules.mk` (`SRC += achordion.c`)
- `scripts/build_air75_v2_via.sh` (build helper)

## Prerequisites
- The NuPhy QMK fork: `https://github.com/nuphy-src/qmk_firmware`
- QMK submodules initialized
- QMK CLI installed via Homebrew (`/opt/homebrew/bin/qmk`)
- ARM GCC toolchain for ChibiOS

## One-time setup
1. Clone and enter the NuPhy fork.
   ```sh
   git clone https://github.com/nuphy-src/qmk_firmware.git
   cd qmk_firmware
   git checkout nuphy-keyboards
   ```

2. Initialize and update submodules.
   ```sh
   git submodule update --init --recursive
   ```

3. Install Python deps for the Homebrew QMK CLI.
   The Homebrew `qmk` CLI uses its own Python under the Cellar. Use the formula prefix:
   ```sh
   \"$(brew --prefix qmk)/libexec/bin/python\" -m pip install -r requirements.txt
   ```

4. Install the ARM toolchain and binutils.
   ```sh
   brew install arm-none-eabi-gcc@8 arm-none-eabi-binutils
   ```

## Build
Use the helper script (recommended):
```sh
./scripts/build_air75_v2_via.sh
```

Or run directly with the required PATH overrides:
```sh
PATH="/opt/homebrew/opt/arm-none-eabi-gcc@8/bin:/opt/homebrew/opt/arm-none-eabi-binutils/bin:$PATH" \
  qmk compile -kb nuphy/air75_v2/ansi -km via
```

## Output
Successful builds produce:
- `.build/nuphy_air75_v2_ansi_via.bin`
- `.build/nuphy_air75_v2_ansi_via.hex`
- `nuphy_air75_v2_ansi_via.bin` (copied to repo root by QMK)

## Common errors and fixes
- `startup_stm32f0xx.mk: No such file or directory`
  - Fix: `git submodule update --init --recursive`

- `Could not find module appdirs!`
  - Fix: install `requirements.txt` using the Homebrew QMK Python:
    `\"$(brew --prefix qmk)/libexec/bin/python\" -m pip install -r requirements.txt`

- `arm-none-eabi-gcc: command not found`
  - Fix: `brew install arm-none-eabi-gcc@8`

- `stdint.h: No such file or directory` with ARM GCC 15.x
  - Fix: use `arm-none-eabi-gcc@8` (includes the needed newlib headers).

- `arm-none-eabi-ar: command not found`
  - Fix: `brew install arm-none-eabi-binutils` and include it on PATH.

## Notes
- Achordion only affects tap-hold keys (mod-tap or layer-tap). Assign any mod-tap in VIA to test behavior.
- VIA dynamic keymap data should remain intact across firmware flashes unless you reset EEPROM.
