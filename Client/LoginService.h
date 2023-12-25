#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include <QObject>

#include "ChatClient.h"

class LoginService : public QObject
{
    Q_OBJECT

public:
    explicit LoginService(ChatClient *chatClient, QObject *parent = nullptr);

private:
    ChatClient *chatClient;
    QString username;
    bool isLoggedIn;

signals:
    void loggedIn();
    void loginFailed(QString reason);

public:
    void loginUser(QString username);
    void processMessage(const QJsonObject &json);
    void logoutUser();
    QString getUsername();

private:
    void login();
};

#endif // LOGINSERVICE_H
