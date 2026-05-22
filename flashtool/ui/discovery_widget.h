#pragma once
#include <QWidget>
#include "../core/discovery.h"

namespace Ui { class DiscoveryWidget; }

class DiscoveryWidget : public QWidget {
    Q_OBJECT
public:
    explicit DiscoveryWidget(QWidget* parent = nullptr);
    ~DiscoveryWidget();

    void setStatus(const QString& msg);   // called by FlashWidget

signals:
    void credentialsReady(const PrinterCredentials& creds);
    void httpLog(const QString& entry);

private slots:
    void onConnectClicked();

private:
    Ui::DiscoveryWidget* ui;
    Discovery            m_discovery;
};
