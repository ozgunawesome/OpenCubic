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

    // HTTP discovery complete → flash widget starts MQTT test
    connect(m_discovery, &DiscoveryWidget::credentialsReady,
            m_flash,     &FlashWidget::startTest);

    // Flash status update → discovery label (shows MQTT status next to IP field)
    connect(m_flash,     &FlashWidget::statusUpdate,
            m_discovery, &DiscoveryWidget::setStatus);

    // HTTP log from discovery widget → flash widget HTTP tab
    connect(m_discovery, &DiscoveryWidget::httpLog,
            m_flash,     &FlashWidget::appendHttpLog);
}

MainWindow::~MainWindow() { delete ui; }
