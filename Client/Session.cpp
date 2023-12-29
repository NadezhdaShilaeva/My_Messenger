#include "Session.h"
#include "ChatClient.h"

Session::Session(LoginService *loginService, ChatService *chatService, QObject *parent)
    : ISession(parent)
    , loginService(loginService)
    , chatService(chatService)
{}

void Session::createSession()
{
    ChatClient* worker = new ChatClient();
    QThread* thread = new QThread();
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &ChatClient::connectToServer);
    connect(worker, &ChatClient::disconnected, thread, &QThread::quit);
    connect(worker, &ChatClient::disconnected, worker, &ChatClient::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    connect(worker, &ChatClient::connected, loginService, &LoginService::login);
    connect(loginService, &LoginService::logInUser, worker, &ChatClient::sendMessage);
    connect(worker, &ChatClient::loginMessage, loginService, &LoginService::processMessage);
    connect(loginService, &LoginService::logOutUser, worker, &ChatClient::disconnectFromServer);
    connect(worker, &ChatClient::disconnected, loginService, &LoginService::disconnected);
    connect(worker, &ChatClient::error, loginService, &LoginService::error);

    connect(chatService, &ChatService::sendMessage, worker, &ChatClient::sendMessage);
    connect(worker, &ChatClient::textMessage, chatService, &ChatService::processTextMessage);
    connect(worker, &ChatClient::textMessageFail, chatService, &ChatService::processTextMessageFail);
    connect(worker, &ChatClient::usersListMessage, chatService, &ChatService::processUsersListMessage);

    thread->start();
}
