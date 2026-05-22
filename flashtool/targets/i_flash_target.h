#pragma once
#include <QString>
#include <QByteArray>
#include "core/firmware_file.h"

class IFlashTarget {
public:
    virtual QString    otaTopic(const QString& modelId,
                                const QString& deviceId) const = 0;
    virtual QString    reportTopic(const QString& modelId,
                                   const QString& deviceId) const = 0;
    virtual bool       validate(const FirmwareFile& fw) const = 0;

    // containerSize / containerMd5: values of the actually served container
    // (ZIP for klipper-go, raw .bin for avata) — NOT the original binary.
    virtual QByteArray buildPayload(const FirmwareFile& fw,
                                    const QString&      firmwareUrl,
                                    qint64              containerSize,
                                    const QString&      containerMd5) const = 0;

    virtual ~IFlashTarget() = default;
};
