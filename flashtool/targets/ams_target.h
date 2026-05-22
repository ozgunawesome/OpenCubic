#pragma once
#include "i_flash_target.h"

// Flash target for ACE Gen 1 (ACE_V...) and Gen 2 (ACE2_V...).
// ACE-ID selects which hub to flash (Gen1: 0–1, Gen2: 0–3).
class AmsTarget final : public IFlashTarget {
public:
    explicit AmsTarget(int aceId);

    QString    otaTopic(const QString& modelId, const QString& deviceId) const override;
    QString    reportTopic(const QString& modelId, const QString& deviceId) const override;
    bool       validate(const FirmwareFile& fw) const override;
    QByteArray buildPayload(const FirmwareFile& fw, const QString& firmwareUrl,
                            qint64 containerSize, const QString& containerMd5) const override;

private:
    int m_aceId;
};
