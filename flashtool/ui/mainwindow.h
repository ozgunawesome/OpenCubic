#pragma once
#include <QMainWindow>

namespace Ui { class MainWindow; }
class DiscoveryWidget;
class FlashWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow*  ui;
    DiscoveryWidget* m_discovery;
    FlashWidget*     m_flash;
};
