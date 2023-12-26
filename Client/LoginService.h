#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include <QObject>

#include "ChatClient.h"
#include "ChatService.h"

class LoginService : public QObject
{
    Q_OBJECT

public:
    explicit LoginService(QObject *parent = nullptr);

private:
    QString username;
    bool isLoggedIn;

signals:
    void logInUser(QString username);
    void logOutUser();
    void loggedIn();
    void loginFailed(QString reason);
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);

public slots:
    void login();
    void processMessage(const QJsonObject &json);
    void onDisconnected();

public:
    void loginUser(QString username, ChatService *chatService);
    void logoutUser();
    QString getUsername();

private:
    void createSession(ChatService *chatService);
};

#endif // LOGINSERVICE_H
