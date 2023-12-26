#include "LoginService.h"
#include "ChatClient.h"


LoginService::LoginService(QObject *parent)
    : QObject(parent)
    , isLoggedIn(false)
{}

void LoginService::loginUser(QString username, ChatService *chatService)
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

    createSession(chatService);
}

void LoginService::createSession(ChatService *chatService)
{
    ChatClient* worker = new ChatClient();
    QThread* thread = new QThread();
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &ChatClient::connectToServer);
    connect(worker, &ChatClient::disconnected, thread, &QThread::quit);
    connect(worker, &ChatClient::disconnected, worker, &ChatClient::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    connect(worker, &ChatClient::connected, this, &LoginService::login);
    connect(this, &LoginService::logInUser, worker, &ChatClient::sendMessage);
    connect(worker, &ChatClient::loginMessage, this, &LoginService::processMessage);
    connect(this, &LoginService::logOutUser, worker, &ChatClient::disconnectFromServer);
    connect(worker, &ChatClient::disconnected, this, &LoginService::onDisconnected);
    connect(worker, &ChatClient::error, this, &LoginService::error);

    connect(chatService, &ChatService::sendMessage, worker, &ChatClient::sendMessage);
    connect(worker, &ChatClient::textMessage, chatService, &ChatService::processTextMessage);
    connect(worker, &ChatClient::textMessageFail, chatService, &ChatService::processTextMessageFail);
    connect(worker, &ChatClient::usersListMessage, chatService, &ChatService::processUsersListMessage);


    thread->start();
}

void LoginService::login()
{
    QJsonObject message;
    message["type"] = QStringLiteral("login");
    message["username"] = username;

    emit logInUser(QJsonDocument(message).toJson());
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

    emit logOutUser();
}

QString LoginService::getUsername()
{
    return username;
}

void LoginService::onDisconnected()
{
    if (!isLoggedIn)
        emit disconnected();
}
