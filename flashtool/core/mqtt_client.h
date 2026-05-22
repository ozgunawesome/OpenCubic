#pragma once
#include <QObject>
#include <QString>
#include <QByteArray>
#include <QSslConfiguration>
#include <memory>

namespace QMQTT { class Client; }

class MqttClient : public QObject {
    Q_OBJECT
public:
    explicit MqttClient(QObject* parent = nullptr);
    ~MqttClient();

    void connectToBroker(const QString& host, quint16 port,
                         const QString& user, const QString& pass,
                         const QString& clientId,
                         const QString& certPem = {},
                         const QString& keyPem  = {});
    void subscribe(const QString& topic);
    void publish(const QString& topic, const QByteArray& payload);
    void disconnectFromBroker();

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString& topic, const QByteArray& payload);
    void error(const QString& message);
    void mqttLog(const QString& entry);  // ">> PUB topic | payload" / "<< SUB topic | data"

private:
    std::unique_ptr<QMQTT::Client> m_client;
};
