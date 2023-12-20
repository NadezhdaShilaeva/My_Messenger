#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QHostAddress>
#include <QtWebSockets/QtWebSockets>
#include <QAbstractSocket>
#include <QObject>

class ChatClient : public QObject
{
    Q_OBJECT

public:
    ChatClient(QObject *parent = nullptr);

public slots:
    void connectToServer();
    void login(QString username);
    void sendMessage(QString text, QString sender, QString receiver);
    void disconnectFromServer();

private slots:
    void onTextMessageReceived(QString message);

signals:
    void connected();
    void loggedIn(QString username);
    void loginError(QString reason);
    void disconnected();
    void messageReceived(QString sender, QString text);
    void error(QAbstractSocket::SocketError socketError);
    void userJoined(QString username);
    void userLeft(QString username);

private:
    QWebSocket *webSocket;
    bool isloggedIn;
    void jsonReceived(const QJsonObject &doc);
};

#endif // CHATCLIENT_H
