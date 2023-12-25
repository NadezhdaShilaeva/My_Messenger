#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <QObject>

#include "ChatClient.h"

class ChatService : public QObject
{
    Q_OBJECT

public:
    explicit ChatService(ChatClient *chatClient, QObject *parent = nullptr);

private:
    ChatClient *chatClient;

signals:
    void loggedIn();
    void loginFailed(QString reason);
    void messageReceived(QString sender, QString text);
    void messageFailed(QString receiver, QString text, QString reason);
    void usersListReceived(const QJsonArray& usersArray);

public:
    void processTextMessage(const QJsonObject &json);
    void processTextMessageFail(const QJsonObject &json);
    void processUsersListMessage(const QJsonObject &json);
    void sendGetUsersRequest();
    void sendMessage(QString text, QString sender, QString receiver);
};

#endif // CHATSERVICE_H
