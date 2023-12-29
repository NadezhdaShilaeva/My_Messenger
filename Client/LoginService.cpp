#include "LoginService.h"
#include "ISession.h"

#include <QJsonObject>
#include <QJsonDocument>

LoginService::LoginService(QObject *parent)
    : QObject(parent)
    , isLoggedIn(false)
{}

void LoginService::loginUser(QString username, ISession *session)
{
    if (isLoggedIn or !this->username.isEmpty())
        return;

    if (username.isEmpty())
    {
        emit loginFailed("Username cannot be empty.");
        return;
    }

    if (username == "Favourites")
    {
        emit loginFailed("Username cannot be Favourites because it is a reserved word.");
        return;
    }

    this->username = username;

    session->createSession();
}

void LoginService::login()
{
    if (username.isEmpty())
        return;

    QJsonObject message;
    message["type"] = QStringLiteral("login");
    message["username"] = username;

    emit logInUser(QJsonDocument(message).toJson());
}

void LoginService::processMessage(const QJsonObject &json)
{
    if (isLoggedIn)
        return;

    const QJsonValue username = json.value("username");
    if (username.isNull() || !username.isString())
        return;

    if (username.toString() != this->username)
        return;

    const QJsonValue result = json.value("success");
    if (result.isNull() || !result.isBool())
        return;

    bool loginSuccess = result.toBool();
    if (loginSuccess)
    {
        isLoggedIn = true;
        emit loggedIn();
        return;
    }

    logoutUser();
    const QJsonValue reason = json.value("reason");
    emit loginFailed(reason.toString());
}

void LoginService::logoutUser()
{
    isLoggedIn = false;
    username.clear();

    emit logOutUser();
}

QString LoginService::getUsername()
{
    return username;
}

bool LoginService::getIsLoggedIn()
{
    return isLoggedIn;
}
