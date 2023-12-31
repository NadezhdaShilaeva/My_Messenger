#include "ChatServiceTest.h"

#include <QList>

class ChatService;

ChatServiceTest::ChatServiceTest()
    : chatService(new ChatService())
    , signalSend(chatService, &ChatService::sendMessage)
    , signalReceived(chatService, &ChatService::messageReceived)
    , signalFailed(chatService, &ChatService::messageFailed)
    , signalUsers(chatService, &ChatService::usersListReceived)
    , signalMessages(chatService, &ChatService::chatMessagesReceived)
{}

ChatServiceTest::~ChatServiceTest()
{}

void ChatServiceTest::cleanup()
{
    signalSend.clear();
    signalReceived.clear();
    signalFailed.clear();
    signalUsers.clear();
    signalMessages.clear();
}

void ChatServiceTest::testProcessTextMessage_validData_emitSignalReceived()
{
    QJsonObject message;
    message["type"] = typeMessage;
    message["text"] = testText;
    message["sender"] = testSender;
    message["receiver"] = testReceiver;

    chatService->processTextMessage(message);

    QCOMPARE(signalReceived.count(), 1);
    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalMessages.count(), 0);

    QList<QVariant> args = signalReceived.takeFirst();
    QCOMPARE(args.at(0).toString(), testSender);
    QCOMPARE(args.at(1).toString(), testText);
}

void ChatServiceTest::testProcessTextMessage_invalidText_notEmitSignalReceived()
{
    QJsonObject message;
    message["type"] = typeMessage;
    message["text"] = 0;
    message["sender"] = testSender;
    message["receiver"] = testReceiver;

    chatService->processTextMessage(message);

    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalMessages.count(), 0);
}

void ChatServiceTest::testProcessTextMessage_invalidSender_notEmitSignalReceived()
{
    QJsonObject message;
    message["type"] = typeMessage;
    message["text"] = testText;
    message["sender"] = 0;
    message["receiver"] = testReceiver;

    chatService->processTextMessage(message);

    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalMessages.count(), 0);
}

void ChatServiceTest::testProcessTextMessageFail_validData_emitSignalFailed()
{
    QJsonObject message;
    message["type"] = typeMessageFail;
    message["text"] = testText;
    message["sender"] = testSender;
    message["receiver"] = testReceiver;
    message["reason"] = "Some reason";

    chatService->processTextMessageFail(message);

    QCOMPARE(signalFailed.count(), 1);
    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalMessages.count(), 0);

    QList<QVariant> args = signalFailed.takeFirst();
    QCOMPARE(args.at(0).toString(), testReceiver);
    QCOMPARE(args.at(1).toString(), testText);
    QCOMPARE(args.at(2).toString(), "Some reason");
}

void ChatServiceTest::testProcessTextMessageFail_invalidText_notEmitSignalFailed()
{
    QJsonObject message;
    message["type"] = typeMessageFail;
    message["text"] = 0;
    message["sender"] = testSender;
    message["receiver"] = testReceiver;
    message["reason"] = "Some reason";

    chatService->processTextMessageFail(message);

    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalMessages.count(), 0);
}

void ChatServiceTest::testProcessTextMessageFail_invalidReceiver_notEmitSignalFailed()
{
    QJsonObject message;
    message["type"] = typeMessageFail;
    message["text"] = testText;
    message["sender"] = testSender;
    message["receiver"] = 0;
    message["reason"] = "Some reason";

    chatService->processTextMessageFail(message);

    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalMessages.count(), 0);
}

void ChatServiceTest::testProcessUsersListMessage_validData_emitSignalUsers()
{
    QJsonObject message;
    message["type"] = typeUsers;
    message["list"] = QJsonArray({"user1", "user2", "user3"});

    chatService->processUsersListMessage(message);

    QCOMPARE(signalUsers.count(), 1);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalMessages.count(), 0);

    QVector<QString> args = signalUsers.takeFirst().at(0).value<QVector<QString>>();

    QCOMPARE(args[0], "user1");
    QCOMPARE(args[1], "user2");
    QCOMPARE(args[2], "user3");
}

void ChatServiceTest::testProcessUsersListMessage_invalidArray_notEmitSignalUsers()
{
    QJsonObject message;
    message["type"] = typeUsers;
    message["list"] = "user1";

    chatService->processUsersListMessage(message);

    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalMessages.count(), 0);
}

void ChatServiceTest::testProcessChatMessages_validData_emitSignalMessages()
{
    QJsonObject message;
    message["type"] = typeUsers;
    QJsonObject message1;
    message1["receiver"] = testReceiver;
    message1["sender"] = testSender;
    message1["text"] = testText;
    message1["time"] = testTime.toString();
    message["list"] = QJsonArray({message1});

    chatService->processChatMessages(message);

    QCOMPARE(signalMessages.count(), 1);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalSend.count(), 0);
}

void ChatServiceTest::testProcessChatMessages_invalidArray_notEmitSignalMessages()
{
    QJsonObject message;
    message["type"] = typeMessages;
    message["list"] = "message1";

    chatService->processChatMessages(message);

    QCOMPARE(signalMessages.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalSend.count(), 0);
}

void ChatServiceTest::testSendGetUsersRequest_emitSignalSend()
{
    chatService->sendGetUsersRequest();

    QCOMPARE(signalSend.count(), 1);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalMessages.count(), 0);

    QString message = signalSend.takeFirst().at(0).toString();
    QJsonObject json = QJsonDocument::fromJson(message.toLocal8Bit()).object();
    QJsonValue type = json.value("type");

    QCOMPARE(type, typeUsers);
}

void ChatServiceTest::testSendTextMessage_validData_emitSignalSend()
{
    chatService->sendTextMessage(testText, testSender, testReceiver, testTime);

    QCOMPARE(signalSend.count(), 1);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalMessages.count(), 0);

    QString message = signalSend.takeFirst().at(0).toString();
    QJsonObject json = QJsonDocument::fromJson(message.toLocal8Bit()).object();
    QString type = json.value("type").toString();
    QString text = json.value("text").toString();
    QString sender = json.value("sender").toString();
    QString receiver = json.value("receiver").toString();
    QTime time = QTime::fromString(json.value("time").toString());

    QCOMPARE(type, typeMessage);
    QCOMPARE(text, testText);
    QCOMPARE(sender, testSender);
    QCOMPARE(receiver, testReceiver);
    QCOMPARE(time, testTime);
}

void ChatServiceTest::testSendTextMessage_invalidText_notEmitSignalSend()
{
    chatService->sendTextMessage(emptyString, testSender, testReceiver, testTime);

    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalMessages.count(), 0);
}

void ChatServiceTest::testSendTextMessage_invalidSender_notEmitSignalSend()
{
    chatService->sendTextMessage(testText, emptyString, testReceiver, testTime);

    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalMessages.count(), 0);
}

void ChatServiceTest::testSendTextMessage_invalidReceiver_notEmitSignalSend()
{
    chatService->sendTextMessage(testText, testSender, emptyString, testTime);

    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
    QCOMPARE(signalMessages.count(), 0);
}

//QTEST_MAIN(ChatServiceTest)
