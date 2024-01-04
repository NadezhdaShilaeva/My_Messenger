#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <QObject>
#include <QTime>
#include <QVector>

#include "Message.h"

class ChatService : public QObject
{
    Q_OBJECT

public:
    explicit ChatService(QObject *parent = nullptr);

signals:
    void sendMessage(QString message);
    void messageReceived(QString sender, QString text, QTime time);
    void messageFailed(QString receiver, QString text, QString reason);
    void chatMessagesReceived(const QVector<Message>& messagesArray);
    void usersListReceived(const QVector<QString>& usersArray);

public slots:
    void processTextMessage(const QJsonObject &json);
    void processTextMessageFail(const QJsonObject &json);
    void processChatMessages(const QJsonObject &json);
    void processUsersListMessage(const QJsonObject &json);

public:
    void sendGetUsersRequest();
    void sendTextMessage(QString text, QString sender, QString receiver, QTime time);
};

#endif // CHATSERVICE_H
