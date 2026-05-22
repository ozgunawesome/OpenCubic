#include "firmware_file.h"
#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QRegularExpression>

FirmwareFile FirmwareFile::load(const QString& path)
{
    FirmwareFile fw;
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly))
        return fw;

    QByteArray data = f.readAll();
    fw.path = path;
    fw.name = QFileInfo(path).fileName();
    fw.size = data.size();
    fw.md5  = QCryptographicHash::hash(data, QCryptographicHash::Md5).toHex();

    // Dateiname-Regex → FlashTarget
    // ACE_V\d+..._\d+.bin  → AceGen1
    // ACE2_V\d+..._\d+.bin → AceGen2
    // *.swu                 → PrinterApp
    static const QRegularExpression re_gen1(
        QStringLiteral(R"(^ACE_V\d+[\w.]*_\d+\.bin$)"));
    static const QRegularExpression re_gen2(
        QStringLiteral(R"(^ACE2_V\d+[\w.]*_\d+\.bin$)"));

    if (re_gen1.match(fw.name).hasMatch())
        fw.target = FlashTarget::AceGen1;
    else if (re_gen2.match(fw.name).hasMatch())
        fw.target = FlashTarget::AceGen2;
    else if (fw.name.endsWith(QStringLiteral(".swu"), Qt::CaseInsensitive))
        fw.target = FlashTarget::PrinterApp;
    else
        fw.target = FlashTarget::Unknown;

    return fw;
}
