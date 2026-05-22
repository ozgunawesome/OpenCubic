#pragma once
#include <QString>
#include <QByteArray>
#include "firmware_packager.h"

enum class FlashTarget {
    AceGen1,     // ACE_V\d+..._\d+.bin
    AceGen2,     // ACE2_V\d+..._\d+.bin
    PrinterApp,  // *.swu
    Unknown
};

struct FirmwareFile {
    QString     path;
    QString     name;
    qint64      size   = 0;
    QString     md5;          // hex, lowercase
    FlashTarget target = FlashTarget::Unknown;

    bool isValid() const { return target != FlashTarget::Unknown && size > 0; }

    // Loads file, computes MD5, detects target from filename regex
    static FirmwareFile load(const QString& path);
};
