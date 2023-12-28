#include "ChatServiceTest.h"

#include <QList>

class ChatService;

ChatServiceTest::ChatServiceTest()
    : chatService(new ChatService())
    , signalSend(chatService, &ChatService::sendMessage)
    , signalReceived(chatService, &ChatService::messageReceived)
    , signalFailed(chatService, &ChatService::messageFailed)
    , signalUsers(chatService, &ChatService::usersListReceived)
{}

ChatServiceTest::~ChatServiceTest()
{}

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

    QJsonArray args = signalUsers.takeFirst().at(0).toJsonArray();

    QCOMPARE(args.at(0).toString(), "user1");
    QCOMPARE(args.at(1).toString(), "user2");
    QCOMPARE(args.at(2).toString(), "user3");
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
}

void ChatServiceTest::testSendGetUsersRequest_emitSignalSend()
{
    chatService->sendGetUsersRequest();

    QCOMPARE(signalSend.count(), 1);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);

    QString message = signalSend.takeFirst().at(0).toString();
    QJsonObject json = QJsonDocument::fromJson(message.toLocal8Bit()).object();
    QJsonValue type = json.value("type");

    QCOMPARE(type, typeUsers);
}

void ChatServiceTest::testSendTextMessage_validData_emitSignalSend()
{
    chatService->sendTextMessage(testText, testSender, testReceiver);

    QCOMPARE(signalSend.count(), 1);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);

    QString message = signalSend.takeFirst().at(0).toString();
    QJsonObject json = QJsonDocument::fromJson(message.toLocal8Bit()).object();
    QJsonValue type = json.value("type");
    QJsonValue text = json.value("text");
    QJsonValue sender = json.value("sender");
    QJsonValue receiver = json.value("receiver");

    QCOMPARE(type, typeMessage);
    QCOMPARE(text, testText);
    QCOMPARE(sender, testSender);
    QCOMPARE(receiver, testReceiver);
}

void ChatServiceTest::testSendTextMessage_invalidText_notEmitSignalSend()
{
    chatService->sendTextMessage("", testSender, testReceiver);

    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
}

void ChatServiceTest::testSendTextMessage_invalidSender_notEmitSignalSend()
{
    chatService->sendTextMessage(testText, "", testReceiver);

    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
}

void ChatServiceTest::testSendTextMessage_invalidReceiver_notEmitSignalSend()
{
    chatService->sendTextMessage(testText, testSender, "");

    QCOMPARE(signalSend.count(), 0);
    QCOMPARE(signalUsers.count(), 0);
    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalReceived.count(), 0);
}

QTEST_MAIN(ChatServiceTest)
