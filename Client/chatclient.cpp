#include "ChatClient.h"

#include <QObject>
#include <QNetworkRequest>

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , webSocket(new QWebSocket())
{
    connect(webSocket, &QWebSocket::connected, this, &ChatClient::connected);
    connect(webSocket, &QWebSocket::disconnected, this, &ChatClient::disconnected);
    connect(webSocket, &QWebSocket::textMessageReceived, this, &ChatClient::onTextMessageReceived);
    connect(webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

void ChatClient::connectToServer()
{
    QUrl url("ws://127.0.0.1:8001");

    webSocket->open(url);
}

void ChatClient::disconnectFromServer()
{
    webSocket->close();
}

void ChatClient::sendMessage(QString message)
{
    webSocket->sendTextMessage(message);
}

void ChatClient::onTextMessageReceived(QString message)
{
    jsonReceived(QJsonDocument::fromJson(message.toLocal8Bit()).object());
}

void ChatClient::jsonReceived(const QJsonObject &json)
{
    QJsonValue type = json.value("type");
    if (type.isNull() || !type.isString())
        return;

    if (type.toString().compare("login") == 0)
    {
        emit loginMessage(json);
    }
    else if (type.toString().compare("message") == 0)
    {
        emit textMessage(json);
    }
    else if (type.toString().compare("messageFail") == 0)
    {
        emit textMessageFail(json);
    }
    else if (type.toString().compare("users") == 0)
    {
        emit usersListMessage(json);
    }
}

void ChatClient::onError(QAbstractSocket::SocketError socketError)
{
    emit error(socketError);
}
