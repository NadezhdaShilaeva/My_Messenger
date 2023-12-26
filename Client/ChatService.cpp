#include "ChatService.h"

#include <QJsonArray>

ChatService::ChatService(QObject *parent) :
    QObject(parent)
{}

void ChatService::processTextMessage(const QJsonObject &json)
{
    QJsonValue text = json.value("text");
    QJsonValue sender = json.value("sender");
    if (text.isNull() || !text.isString())
        return;

    if (sender.isNull() || !sender.isString())
        return;

    emit messageReceived(sender.toString(), text.toString());
}

void ChatService::processTextMessageFail(const QJsonObject &json)
{
    QJsonValue text = json.value("text");
    QJsonValue receiver = json.value("receiver");
    QJsonValue reason = json.value("reason");
    if (text.isNull() || !text.isString())
        return;

    if (receiver.isNull() || !receiver.isString())
        return;

    emit messageFailed(receiver.toString(), text.toString(), reason.toString());
}

void ChatService::processUsersListMessage(const QJsonObject &json)
{
    QJsonValue usersList = json.value("list");
    if (usersList.isNull() || !usersList.isArray())
        return;

    QJsonArray usersArray = usersList.toArray();

    emit usersListReceived(usersArray);
}

void ChatService::sendGetUsersRequest()
{
    QJsonObject message;
    message["type"] = QStringLiteral("users");

    emit sendMessage(QJsonDocument(message).toJson());
    //chatClient->sendMessage(QJsonDocument(message).toJson());
}

void ChatService::sendTextMessage(QString text, QString sender, QString receiver)
{
    if (text.isEmpty() or sender.isEmpty() or receiver.isEmpty())
        return;

    QJsonObject message;
    message["type"] = QStringLiteral("message");
    message["text"] = text;
    message["sender"] = sender;
    message["receiver"] = receiver;

    emit sendMessage(QJsonDocument(message).toJson());
    //chatClient->sendMessage(QJsonDocument(message).toJson());
}
