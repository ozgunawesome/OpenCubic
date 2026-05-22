# How to Flash the ACE CFW

## Requirements

- Anycubic ACE Gen 1 connected to your Kobra printer
- Printer must be in **LAN mode** (not connected to Anycubic cloud)
- Printer and PC on the same local network
- ACE Flash Tool — download the pre-built Windows binary from
  [Releases](https://github.com/Jupsi/OpenCubic/releases), or
  [build from source](../README.md#build-the-flash-tool) (Qt 5.15+, CMake 3.20+, MSVC)

## Steps

1. Download the latest `.bin` from [Releases](https://github.com/Jupsi/OpenCubic/releases)
2. Open `AceFlashTool.exe`
3. Enter your printer's IP address
4. Click **Test Connection** and wait until the log shows `Test OK - Connection remains active`
5. Select the .bin file
6. Click **Flash**

The ACE will reboot automatically after flashing (~30 seconds).

## Recovery

### Flash Tool Recovery (recommended)

In most cases a bad flash can be recovered using the same flash tool. Flash the original
Anycubic firmware from the [`originalFirmware/`](../originalFirmware/) folder — as long as
the ACE bootloader is still intact, this will restore the unit to a working state.

### SWD Recovery (last resort)

If the ACE no longer responds to the flash tool at all, it can be recovered via SWD using a
GD-Link adapter. See your Kobra printer's documentation for the SWD pinout on the ACE board.
