#pragma once
#include "i_flash_target.h"

// Flash target for printer application firmware (.swu).
// No ACE-ID needed — targets the printer itself.
class PrinterAppTarget final : public IFlashTarget {
public:
    QString    otaTopic(const QString& modelId, const QString& deviceId) const override;
    QString    reportTopic(const QString& modelId, const QString& deviceId) const override;
    bool       validate(const FirmwareFile& fw) const override;
    QByteArray buildPayload(const FirmwareFile& fw, const QString& firmwareUrl,
                            qint64 containerSize, const QString& containerMd5) const override;
};
