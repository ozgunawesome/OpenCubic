# Changelog

## CFW v1.0 — 2026-05-22

> Based on official Anycubic ACE firmware **v1.3.863**

### Added
- Multi-vendor NFC framework: Anycubic Gen 1/Gen 2, Bambu Lab, Elegoo, TigerTag, OpenSpool, OpenPrintTag
- Bambu Lab MIFARE Classic support (HKDF-SHA256 sector key derivation)
- SKU propagation for all NFC parsers — slicer edit lock active (rfid=2) for all recognized spools
- RxGain increased to 48 dB (+15 dB vs. default 33 dB) for all NFC reader slots
- Case-start immediate read: no full spool rotation needed when chip is already at the reader on insertion

### Fixed
- NFC color byte order: Anycubic and Bambu colors now display correctly in the slicer
- Hub-tag stop strategy: Bambu spools (hub-mounted tag) use a soft stop at 5 mm/s to reduce inertia overshoot after motor stop
- Partial MIFARE read resilience: sector 2 auth failure no longer discards valid data from sectors 0+1
- GCC -O2 SPI delay: `volatile` keyword added to bitbang SPI delay loops (NFC was completely inactive without this)
- NFC timer: increased from 1 ms to 10 ms for both NTAG and MIFARE block reads/auth (response time ~1.84 ms at 106 kbps)
- Boot crash on GCC: static C++ objects with virtual destructors replaced with heap allocation to avoid `__cxa_guard_acquire` (LDREX/STREX) crash on FreeRTOS startup
