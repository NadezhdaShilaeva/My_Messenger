#include "chatclient.h"
#include <QObject>

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , isloggedIn(false)
{
    connect(webSocket, &QWebSocket::connected, this, &ChatClient::connected);
    connect(webSocket, &QWebSocket::disconnected, this, &ChatClient::disconnected);
    connect(webSocket, &QWebSocket::textMessageReceived, this, &ChatClient::onTextMessageReceived);
    //connect(webSocket, &QWebSocket::error, this, &ChatClient::error);
    connect(webSocket, &QWebSocket::disconnected, this, [this]()->void{isloggedIn = false;});
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

void ChatClient::login(QString username)
{
    QJsonObject message;
    message["type"] = QStringLiteral("login");
    message["username"] = username;

    webSocket->sendTextMessage(QJsonDocument(message).toJson());
}

void ChatClient::sendMessage(QString text, QString sender, QString receiver)
{
    if (text.isEmpty() or sender.isEmpty() or receiver.isEmpty())
        return;

    QJsonObject message;
    message["type"] = QStringLiteral("message");
    message["text"] = text;
    message["sender"] = sender;
    message["receiver"] = receiver;

    webSocket->sendTextMessage(QJsonDocument(message).toJson(QJsonDocument::Compact));
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

    if (type.toString().compare("login", Qt::CaseInsensitive) == 0)
    {
        if (isloggedIn)
            return;

        QJsonValue result = json.value("success");
        if (result.isNull() || !result.isBool())
            return;

        QString username = json.value("username").toString();
        bool loginSuccess = result.toBool();
        if (loginSuccess) {
            isloggedIn = true;
            emit loggedIn(username);
            return;
        }

        QJsonValue reason = json.value("reason");
        emit loginError(reason.toString());
    }
    else if (type.toString().compare("message", Qt::CaseInsensitive) == 0)
    {
        QJsonValue text = json.value("text");
        QJsonValue sender = json.value("sender");
        if (text.isNull() || !text.isString())
            return;

        if (sender.isNull() || !sender.isString())
            return;

        emit messageReceived(sender.toString(), text.toString());
    }
    else if (type.toString().compare("newuser", Qt::CaseInsensitive) == 0)
    {
        QJsonValue username = json.value(QLatin1String("username"));
        if (username.isNull() || !username.isString())
            return;

        emit userJoined(username.toString());
    }
    else if (type.toString().compare(QLatin1String("userdisconnected"), Qt::CaseInsensitive) == 0)
    {
        QJsonValue username = json.value(QLatin1String("username"));
        if (username.isNull() || !username.isString())
            return;

        emit userLeft(username.toString());
    }
}

