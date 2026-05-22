# How to Flash the ACE CFW

## Requirements

- Anycubic ACE Gen 1 connected to your Kobra printer
- Printer and PC on the same local network
- ACE Flash Tool (see README)

## Steps

1. Download the latest .bin from [Releases](https://github.com/Jupsi/OpenCubic/releases)
2. Open the ACE Flash Tool
3. Enter your printer's IP address
4. Click **Test Connection** and wait until the log shows `Test OK - Connection remains active`
5. Select the .bin file
6. Click **Flash**

The ACE will reboot automatically after flashing (~30 seconds).

## Recovery (SWD)

If the ACE doesn't respond after a bad flash, it can be recovered via SWD using a GD-Link adapter.
See your Kobra printer's documentation for the SWD pinout on the ACE board.
