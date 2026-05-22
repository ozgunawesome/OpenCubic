#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "discovery_widget.h"
#include "flash_widget.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_discovery(new DiscoveryWidget(this))
    , m_flash(new FlashWidget(this))
{
    ui->setupUi(this);

    auto* layout = new QVBoxLayout(ui->centralWidget);
    layout->addWidget(m_discovery);
    layout->addWidget(m_flash);
    layout->setContentsMargins(8, 8, 8, 8);

    // HTTP-Discovery → Flash startet MQTT-Test
    connect(m_discovery, &DiscoveryWidget::credentialsReady,
            m_flash,     &FlashWidget::startTest);

    // Flash-Status-Update → Discovery-Label (zeigt MQTT-Status neben IP-Feld)
    connect(m_flash,     &FlashWidget::statusUpdate,
            m_discovery, &DiscoveryWidget::setStatus);

    // HTTP-Log vom Discovery-Widget → Flash-Widget HTTP-Tab
    connect(m_discovery, &DiscoveryWidget::httpLog,
            m_flash,     &FlashWidget::appendHttpLog);
}

MainWindow::~MainWindow() { delete ui; }
