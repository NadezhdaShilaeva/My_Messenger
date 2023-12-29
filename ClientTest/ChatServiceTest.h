#ifndef CHATSERVICETEST_H
#define CHATSERVICETEST_H

#include <QtTest>
#include <QCoreApplication>

#include "ChatService.h"

class ChatServiceTest : public QObject
{
    Q_OBJECT

public:
    ChatServiceTest();
    ~ChatServiceTest();

private slots:
    void testProcessTextMessage_validData_emitSignalReceived();
    void testProcessTextMessage_invalidText_notEmitSignalReceived();
    void testProcessTextMessage_invalidSender_notEmitSignalReceived();

    void testProcessTextMessageFail_validData_emitSignalFailed();
    void testProcessTextMessageFail_invalidText_notEmitSignalFailed();
    void testProcessTextMessageFail_invalidReceiver_notEmitSignalFailed();

    void testProcessUsersListMessage_validData_emitSignalUsers();
    void testProcessUsersListMessage_invalidArray_notEmitSignalUsers();

    void testSendGetUsersRequest_emitSignalSend();

    void testSendTextMessage_validData_emitSignalSend();
    void testSendTextMessage_invalidText_notEmitSignalSend();
    void testSendTextMessage_invalidSender_notEmitSignalSend();
    void testSendTextMessage_invalidReceiver_notEmitSignalSend();

private:
    ChatService *chatService;

    QSignalSpy signalSend;
    QSignalSpy signalReceived;
    QSignalSpy signalFailed;
    QSignalSpy signalUsers;

    const QString typeMessage = "message";
    const QString typeMessageFail = "messageFail";
    const QString typeUsers = "users";

    const QString testText = "Hello";
    const QString testSender = "user1";
    const QString testReceiver = "user2";
};

#endif // CHATSERVICETEST_H
