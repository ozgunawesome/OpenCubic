# Changelog — OpenCubic

Public release notes for the **ACE Flash Tool** and the **Custom Firmware (CFW)** for Anycubic ACE
filament systems (ACE 1 Pro and ACE 2 Pro).

---

## ACE Flash Tool

### v1.0.1 — 2026-05-29

#### Added
- **ACE 2 Pro support** (AVATA-stack printers, e.g. Kobra X): flashing the Gen 2 CFW is now enabled.
- The previous blanket AVATA block was replaced by a firmware/printer **mismatch guard**:
  - AVATA stack + `ACE2_V…` image → **allowed**
  - AVATA stack + `ACE_V…` (Gen 1) image → blocked (soft-brick protection)
  - KlipperGo stack + `ACE_V…` image → **allowed**
  - KlipperGo stack + `ACE2_V…` image → blocked (soft-brick protection)

### v1.0 — 2026-05-22

- Initial release: LAN/MQTT printer discovery + OTA flashing of the CFW onto **ACE Gen 1**
  (KlipperGo-stack printers, e.g. Kobra 3 / Kobra S1).

---

## CFW — ACE 2 Pro

### v1.0.4 — 2026-05-29

> First CFW for the **ACE 2 Pro**, based on official stock firmware **V1.1.31**.
> Reports version `V1.0.0` to the printer (kept intentionally low so cloud mode still offers the official
> firmware as an update — useful as a recovery image).

#### Added
- Multi-vendor NFC framework (ported from the ACE 1 Pro CFW): **Anycubic, Bambu Lab**, OpenPrintTag,
  OpenSpool, Elegoo, TigerTag. QIDI/Creality are stubs (keys unknown).
- Bambu Lab MIFARE Classic support (HKDF-SHA256 sector key derivation, Crypto1 authentication).
- RxGain increased to 48 dB (+15 dB vs. default 33 dB) for all NFC reader slots
- Integrated as an **additive layer**: the stock Anycubic read path is unchanged; foreign tags are
  handled via a fallback → zero regression for Anycubic spools.

#### Confirmed
- Anycubic NTAG and Bambu Lab MIFARE recognized reliably and stably (material/color/temperature correct).
- The other vendors (OpenPrintTag/OpenSpool/Elegoo/TigerTag) are ported but not yet tested on a real tag.

#### Fixed
- Initial stack pointer used `0x800` instead of `_estack` → the bootloader never jumped to the app.
- C++ `new`/`delete` and `rand()` routed to the FreeRTOS heap.
- IAP signature trailer appended to the image (required by the running firmware to apply an OTA update).
- Stack sizing for the HKDF-SHA256 path; MIFARE re-select before authentication (Bambu read fix).

---

## CFW — ACE 1 Pro

### v1.0 — 2026-05-22

> Based on official Anycubic ACE firmware **v1.3.863**

#### Added
- Multi-vendor NFC framework: Anycubic Gen 1/Gen 2, Bambu Lab, Elegoo, TigerTag, OpenSpool, OpenPrintTag
- Bambu Lab MIFARE Classic support (HKDF-SHA256 sector key derivation)
- SKU propagation for all NFC parsers — slicer edit lock active (rfid=2) for all recognized spools
- RxGain increased to 48 dB (+15 dB vs. default 33 dB) for all NFC reader slots
- Case-start immediate read: no full spool rotation needed when chip is already at the reader on insertion

#### Fixed
- NFC color byte order: Anycubic and Bambu colors now display correctly in the slicer
- Hub-tag stop strategy: Bambu spools (hub-mounted tag) use a soft stop at 5 mm/s to reduce inertia overshoot after motor stop
- Partial MIFARE read resilience: sector 2 auth failure no longer discards valid data from sectors 0+1
- GCC -O2 SPI delay: `volatile` keyword added to bitbang SPI delay loops (NFC was completely inactive without this)
- NFC timer: increased from 1 ms to 10 ms for both NTAG and MIFARE block reads/auth (response time ~1.84 ms at 106 kbps)
- Boot crash on GCC: static C++ objects with virtual destructors replaced with heap allocation to avoid `__cxa_guard_acquire` (LDREX/STREX) crash on FreeRTOS startup
