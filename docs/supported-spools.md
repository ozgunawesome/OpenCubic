# Supported NFC Spool Formats

Same vendor coverage on **both ACE 1 Pro and ACE 2 Pro** — the multi-vendor NFC framework is shared.
"Anycubic Gen 1 / Gen 2" below refers to the Anycubic **tag** variants, not the ACE hardware generation.

| Brand | Chip | Format | SKU | Color | Temp | Status |
|---|---|---|---|---|---|---|
| Anycubic Gen 1 | NTAG215 | Proprietary | ✅ | ✅ | ✅ | ✅ Confirmed (ACE 1 Pro + ACE 2 Pro) |
| Anycubic Gen 2 | NTAG215 + PWD | Proprietary | ✅ | ✅ | ✅ | ✅ Confirmed |
| Bambu Lab | MIFARE Classic 1K | Proprietary + HKDF | ✅ | ✅ | ✅ | ✅ Confirmed (ACE 1 Pro + ACE 2 Pro) |
| Elegoo | NTAG213 | Open source | ✅ | ✅ | ✅ | ✅ Implemented / untested |
| TigerTag | NTAG213 | Open | ✅ | ✅ | ✅ | ✅ Implemented / untested |
| OpenSpool | NTAG215/216 | JSON/NDEF | ✅ | ✅ | ✅ | ✅ Implemented / untested |
| OpenPrintTag (Prusa) | NTAG213/215 | CBOR/NDEF | ✅ | ✅ | ✅ | ✅ Implemented / untested |
| QIDI | MIFARE Classic | Proprietary | — | — | — | 🔄 Unknown AES keys |
| Creality | MIFARE Classic | AES encrypted | — | — | — | 🔄 Unknown AES keys |

> "Confirmed" = verified on real hardware. "Implemented / untested" = parser ported (formats from
> community reverse-engineering), no physical tag tested yet. "Unknown AES keys" = stub; keys not
> publicly documented.
