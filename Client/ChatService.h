#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <QObject>

class ChatService : public QObject
{
    Q_OBJECT

public:
    explicit ChatService(QObject *parent = nullptr);

signals:
    void sendMessage(QString message);
    void messageReceived(QString sender, QString text);
    void messageFailed(QString receiver, QString text, QString reason);
    void usersListReceived(const QJsonArray& usersArray);

public slots:
    void processTextMessage(const QJsonObject &json);
    void processTextMessageFail(const QJsonObject &json);
    void processUsersListMessage(const QJsonObject &json);

public:
    void sendGetUsersRequest();
    void sendTextMessage(QString text, QString sender, QString receiver);
};

#endif // CHATSERVICE_H
