#include "ams_target.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QDateTime>
#include <QUuid>

AmsTarget::AmsTarget(int aceId) : m_aceId(aceId) {}

QString AmsTarget::otaTopic(const QString& modelId, const QString& deviceId) const
{
    return QStringLiteral(
        "anycubic/anycubicCloud/v1/public/printer/%1/%2/ota/multiColorBox/%3")
        .arg(modelId, deviceId).arg(m_aceId);
}

QString AmsTarget::reportTopic(const QString& modelId, const QString& deviceId) const
{
    return QStringLiteral(
        "anycubic/anycubicCloud/v1/printer/public/%1/%2/ota/multiColorBox/%3/report")
        .arg(modelId, deviceId).arg(m_aceId);
}

bool AmsTarget::validate(const FirmwareFile& fw) const
{
    if (fw.target == FlashTarget::AceGen1) {
        return m_aceId >= 0 && m_aceId <= 1;   // Gen1: max 2 units
    }
    if (fw.target == FlashTarget::AceGen2) {
        return m_aceId >= 0 && m_aceId <= 3;   // Gen2: max 4 units
    }
    return false;
}

QByteArray AmsTarget::buildPayload(const FirmwareFile& fw,
                                    const QString& firmwareUrl,
                                    qint64         containerSize,
                                    const QString& containerMd5) const
{
    // Version string from filename: ACE_V1.3.5_20260519.bin -> "1.3.5"
    static const QRegularExpression re(QStringLiteral(R"(ACE2?_V([\d.]+\w*)_\d+\.bin)"));
    auto m = re.match(fw.name);
    QString version = m.hasMatch() ? m.captured(1) : QStringLiteral("1.0.0");

    // Firmware >= 2.7.x requires a model_id field matching the connected hub
    // (40001 = ACE Pro Gen1, 40002 = ACE 2 Pro).
    const int modelId = (fw.target == FlashTarget::AceGen2) ? 40002 : 40001;

    QJsonObject data{
        { QStringLiteral("model_id"),         modelId },
        { QStringLiteral("firmware_url"),     firmwareUrl },
        { QStringLiteral("firmware_name"),    fw.name },
        { QStringLiteral("firmware_version"), version },
        { QStringLiteral("firmware_size"),    containerSize },   // container size
        { QStringLiteral("firmware_md5"),     containerMd5  },   // container MD5
    };

    QJsonObject root{
        { QStringLiteral("type"),      QStringLiteral("ota") },
        { QStringLiteral("action"),    QStringLiteral("update") },
        { QStringLiteral("timestamp"), QDateTime::currentMSecsSinceEpoch() },
        { QStringLiteral("msgid"),     QUuid::createUuid().toString(QUuid::WithoutBraces) },
        { QStringLiteral("data"),      data },
    };

    return QJsonDocument(root).toJson(QJsonDocument::Compact);
}
