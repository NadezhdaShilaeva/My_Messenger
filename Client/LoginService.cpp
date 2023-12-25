#include "LoginService.h"

LoginService::LoginService(ChatClient *chatClient, QObject *parent)
    : QObject(parent)
    , chatClient(chatClient)
    , isLoggedIn(false)
{
    connect(chatClient, &ChatClient::connected, this, &LoginService::login);
    connect(chatClient, &ChatClient::loginMessage, this, &LoginService::processMessage);
}

void LoginService::loginUser(QString username)
{
    if (isLoggedIn or !this->username.isEmpty() or username.isEmpty())
        return;

    this->username = username;

    chatClient->connectToServer();
}

void LoginService::login()
{
    QJsonObject message;
    message["type"] = QStringLiteral("login");
    message["username"] = username;

    chatClient->sendMessage(QJsonDocument(message).toJson());
}

void LoginService::processMessage(const QJsonObject &json)
{
    if (isLoggedIn)
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

    chatClient->disconnectFromServer();
}

QString LoginService::getUsername()
{
    return username;
}
