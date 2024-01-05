#pragma once

#include "gtest/gtest.h"
#include "../Server/Message.cpp"
#include "../Server/InMemoryUserRepository.h"
#include "../Server/InMemoryMessageRepository.cpp"
#include "../Server/ChatService.cpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(TestChatService, SaveMessage_MessageSaved)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto messageRepository = std::make_shared<InMemoryMessageRepository>();
	auto chatService = new ChatService(userRepository, messageRepository);

	std::string sender = "user1";
	std::string receiver = "user2";
	std::string text = "hello";
	std::string time = "12:48:45";
	User user1 = User(sender, "123", "salt");
	User user2 = User(receiver, "456", "salt");
	userRepository->save(user1);
	userRepository->save(user2);
	chatService->saveMessage(receiver, sender, text, time);

	auto message = messageRepository->findBySender(user1).front();

	EXPECT_EQ(user1, message.getSender());
	EXPECT_EQ(user2, message.getReceiver());
	EXPECT_EQ("hello", message.getText());
	EXPECT_EQ("12:48:45", message.getTime());
}

TEST(TestChatService, CreateChatMessagesList_MessagesListCreated)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto messageRepository = std::make_shared<InMemoryMessageRepository>();
	auto chatService = new ChatService(userRepository, messageRepository);

	User user1 = User("user1", "123", "salt");
	userRepository->save(user1);
	User user2 = User("user2", "456", "salt");
	userRepository->save(user2);
	Message message1 = Message(user1, user2, "hello", "12:48:45");
	messageRepository->save(message1);
	Message message2 = Message(user2, user1, "hi", "12:48:54");
	messageRepository->save(message2);
	Message message3 = Message(user2, user2, "privet", "12:48:59");
	messageRepository->save(message3);

	std::string messages = chatService->createChatMessagesList("user1");
	json messagesJson = json::parse(messages);

	EXPECT_EQ(2, messagesJson["list"].size());
	EXPECT_EQ(user1.getUsername(), messagesJson["list"].at(0)["receiver"]);
	EXPECT_EQ(user2.getUsername(), messagesJson["list"].at(0)["sender"]);
	EXPECT_EQ("hello", messagesJson["list"].at(0)["text"]);
	EXPECT_EQ("12:48:45", messagesJson["list"].at(0)["time"]);
	EXPECT_EQ(user2.getUsername(), messagesJson["list"].at(1)["receiver"]);
	EXPECT_EQ(user1.getUsername(), messagesJson["list"].at(1)["sender"]);
	EXPECT_EQ("hi", messagesJson["list"].at(1)["text"]);
	EXPECT_EQ("12:48:54", messagesJson["list"].at(1)["time"]);
}

TEST(TestChatService, CreateFailMessage_FailMessageCreated)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto messageRepository = std::make_shared<InMemoryMessageRepository>();
	auto chatService = new ChatService(userRepository, messageRepository);
	std::string message = "{\"type\": \"message\", \"sender\": \"user1\", \"receiver\": \"user2\", \"text\": \"hello\", \"time\": \"12:48:45\"}";

	std::string reply = chatService->createFailMessage(message);
	json replyJson = json::parse(reply);

	EXPECT_EQ("messageFail", replyJson["type"]);
	EXPECT_EQ("user1", replyJson["sender"]);
	EXPECT_EQ("user2", replyJson["receiver"]);
	EXPECT_EQ("hello", replyJson["text"]);
	EXPECT_EQ("12:48:45", replyJson["time"]);
	EXPECT_EQ("Message was not delivered. user2 no longer exists.", replyJson["reason"]);
}

TEST(TestChatService, CreateUsersList_UsersListCreated)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto messageRepository = std::make_shared<InMemoryMessageRepository>();
	auto chatService = new ChatService(userRepository, messageRepository);
	userRepository->save(User("user1", "123456", "salt"));
	userRepository->save(User("user2", "123457", "salt"));
	userRepository->save(User("user3", "123458", "salt"));

	std::string reply = chatService->createUsersList();
	json replyJson = json::parse(reply);

	EXPECT_EQ("users", replyJson["type"]);
	EXPECT_EQ(3, replyJson["list"].size());
	EXPECT_TRUE(std::find(replyJson["list"].begin(), replyJson["list"].end(), "user1") != replyJson["list"].end());
	EXPECT_TRUE(std::find(replyJson["list"].begin(), replyJson["list"].end(), "user2") != replyJson["list"].end());
	EXPECT_TRUE(std::find(replyJson["list"].begin(), replyJson["list"].end(), "user3") != replyJson["list"].end());
}