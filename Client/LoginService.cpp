#include "LoginService.h"
#include "ISession.h"

#include <QJsonObject>
#include <QJsonDocument>

LoginService::LoginService(QObject *parent)
    : QObject(parent)
    , isLoggedIn(false)
{}

bool LoginService::checkCredentials(QString username, QString password)
{
    if (username.isEmpty())
    {
        emit loginFailed("Username cannot be empty.");
        return false;
    }

    if (username == "Favourites")
    {
        emit loginFailed("Username cannot be Favourites because it is a reserved word.");
        return false;
    }

    if (password.isEmpty())
    {
        emit loginFailed("Password cannot be empty.");
        return false;
    }

    return true;
}

void LoginService::loginUser(QString username, QString password, QString type)
{
    if (isLoggedIn or !this->username.isEmpty())
        return;

    if (!checkCredentials(username, password))
    {
        logoutUser();
        return;
    }

    this->username = username;

    QJsonObject message;
    message["type"] = type;
    message["username"] = username;
    message["password"] = password;

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
