#include "discovery_widget.h"
#include "ui_discovery_widget.h"
#include <iostream>

DiscoveryWidget::DiscoveryWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DiscoveryWidget)
{
    ui->setupUi(this);
    connect(ui->btnDiscover, &QPushButton::clicked, this, &DiscoveryWidget::onConnectClicked);

    connect(&m_discovery, &Discovery::credentialsReady, this, [this](const PrinterCredentials& c) {
        ui->labelStatus->setText(QStringLiteral("OK  %1 (%2)").arg(c.modelName, c.ip));
        ui->btnDiscover->setEnabled(true);
        ui->lineIp->setEnabled(true);
        ui->linePort->setEnabled(true);
        emit credentialsReady(c);
    });
    connect(&m_discovery, &Discovery::error, this, [this](const QString& msg) {
        ui->labelStatus->setText(QStringLiteral("ERR ") + msg);
        ui->btnDiscover->setEnabled(true);
        ui->lineIp->setEnabled(true);
        ui->linePort->setEnabled(true);
    });
    connect(&m_discovery, &Discovery::httpLog, this, &DiscoveryWidget::httpLog);
}

DiscoveryWidget::~DiscoveryWidget() { delete ui; }

void DiscoveryWidget::setStatus(const QString& msg)
{
    ui->labelStatus->setText(msg);
}

void DiscoveryWidget::onConnectClicked()
{
    QString ip = ui->lineIp->text().trimmed();
    QString port = ui->linePort->text().trimmed();
    std::cout << "DiscoveryWidget: discover " << ip.toStdString() << ":" << port.toStdString() << std::endl;
    if (ip.isEmpty() || port.isEmpty()) return;
    ui->labelStatus->setText(QStringLiteral("HTTP Discovery..."));
    ui->btnDiscover->setEnabled(false);
    ui->lineIp->setEnabled(false);
    ui->linePort->setEnabled(false);
    m_discovery.discover(ip, QString::fromStdString(port.toStdString()).toULongLong());
}
