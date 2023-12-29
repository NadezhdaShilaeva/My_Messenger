#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include <QObject>
#include <QAbstractSocket>

#include "ISession.h"

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

public:
    void loginUser(QString username, ISession *session);
    void logoutUser();
    QString getUsername();
    bool getIsLoggedIn();
};

#endif // LOGINSERVICE_H
