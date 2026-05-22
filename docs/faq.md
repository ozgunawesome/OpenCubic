# FAQ

**Q: Does this work with ACE Gen 2?**  
A: No, this firmware is for ACE Gen 1 (GD32F303) only.

**Q: My Bambu spool is not recognized**  
A: The firmware increases both TX power and RX gain for better read range. If the spool is still
not recognized, the NFC chip may be positioned too far from the reader toward the center of the
spool hub. Try rotating the spool slightly before inserting, or re-seat it so the hub tag is
closer to the reader side of the slot.

**Q: The slicer shows the wrong color for my spool**  
A: Update to v1.3.863 or later — color byte order was fixed in this release.

**Q: Can I go back to the original firmware?**  
A: Yes. Flash the original Anycubic firmware using the same flash tool.

**Q: My printer shows as "unknown" in the Flash Tool**  
A: The printer type is detected by model ID. Not all model IDs are mapped yet, as printer
configuration files are not publicly available for every model. If you know the model ID of
your printer, please open an issue with the model ID and printer name, or submit a pull request
with the correct mapping in `firmware_packager.cpp`.
