#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QHostAddress>
#include <QtWebSockets/QtWebSockets>
#include <QAbstractSocket>
#include <QObject>
#include <QThread>

class ChatClient : public QObject
{
    Q_OBJECT

public:
    ChatClient(QObject *parent = nullptr);

public slots:
    void connectToServer();
    void sendMessage(QString message);
    void disconnectFromServer();

private slots:
    void onTextMessageReceived(QString message);
    void onError(QAbstractSocket::SocketError socketError);

signals:
    void connected();
    void loginMessage(const QJsonObject &json);
    void chatMessages(const QJsonObject &json);
    void textMessage(const QJsonObject &json);
    void textMessageFail(const QJsonObject &json);
    void usersListMessage(const QJsonObject &json);
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);

private:
    QWebSocket *webSocket = nullptr;
    void jsonReceived(const QJsonObject &doc);
};

#endif // CHATCLIENT_H
