#include "ChatService.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

ChatService::ChatService(QObject *parent) :
    QObject(parent)
{}

void ChatService::processTextMessage(const QJsonObject &json)
{
    QJsonValue text = json.value("text");
    QJsonValue sender = json.value("sender");
    QJsonValue time = json.value("time");

    if (text.isNull() || !text.isString())
        return;

    if (sender.isNull() || !sender.isString())
        return;

    if (time.isNull())
        return;

    emit messageReceived(sender.toString(), text.toString(), QTime::fromString(time.toString()));
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

    QVector<QString> usersVector;
    for (int i = 0; i < usersArray.size(); ++i)
    {
        usersVector.push_back(usersArray.at(i).toString());
    }

    emit usersListReceived(usersVector);
}

void ChatService::processChatMessages(const QJsonObject &json)
{
    QJsonValue messagesList = json.value("list");
    if (messagesList.isNull() || !messagesList.isArray())
        return;

    QJsonArray messagesArray = messagesList.toArray();

    QVector<Message> messagesVector;
    for (int i = 0; i < messagesArray.size(); ++i)
    {
        QJsonObject message = messagesArray.at(i).toObject();

        QString receiver = message.value("receiver").toString();
        QString sender = message.value("sender").toString();
        QString text = message.value("text").toString();
        QTime time = QTime::fromString(message.value("time").toString());

        messagesVector.push_back(Message(sender, receiver, text, time));
    }

    emit chatMessagesReceived(messagesVector);
}

void ChatService::sendGetUsersRequest()
{
    QJsonObject message;
    message["type"] = "users";

    emit sendMessage(QJsonDocument(message).toJson());
}

void ChatService::sendTextMessage(QString text, QString sender, QString receiver, QTime time)
{
    if (text.isEmpty() or sender.isEmpty() or receiver.isEmpty())
        return;

    QJsonObject message;
    message["type"] = "message";
    message["text"] = text;
    message["sender"] = sender;
    message["receiver"] = receiver;
    message["time"] = time.toString();

    emit sendMessage(QJsonDocument(message).toJson());
}
