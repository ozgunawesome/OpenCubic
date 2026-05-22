#include "printer_app_target.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QDateTime>
#include <QUuid>

QString PrinterAppTarget::otaTopic(const QString& modelId, const QString& deviceId) const
{
    return QStringLiteral(
        "anycubic/anycubicCloud/v1/public/printer/%1/%2/ota")
        .arg(modelId, deviceId);
}

QString PrinterAppTarget::reportTopic(const QString& modelId, const QString& deviceId) const
{
    return QStringLiteral(
        "anycubic/anycubicCloud/v1/printer/public/%1/%2/ota/report")
        .arg(modelId, deviceId);
}

bool PrinterAppTarget::validate(const FirmwareFile& fw) const
{
    return fw.target == FlashTarget::PrinterApp;
}

QByteArray PrinterAppTarget::buildPayload(const FirmwareFile& fw,
                                           const QString& firmwareUrl,
                                           qint64         containerSize,
                                           const QString& containerMd5) const
{
    // Versionsstring aus .swu-Dateiname extrahieren (best-effort)
    static const QRegularExpression re(QStringLiteral(R"(_(V[\d.]+)_)"));
    auto m = re.match(fw.name);
    QString version = m.hasMatch() ? m.captured(1) : QStringLiteral("V1.0.0");

    QJsonObject data{
        { QStringLiteral("firmware_url"),     firmwareUrl },
        { QStringLiteral("firmware_name"),    fw.name },
        { QStringLiteral("firmware_version"), version },
        { QStringLiteral("firmware_size"),    containerSize },
        { QStringLiteral("firmware_md5"),     containerMd5  },
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
