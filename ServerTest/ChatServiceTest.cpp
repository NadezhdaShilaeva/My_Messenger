#pragma once

#include "gtest/gtest.h"
#include "../Server/ChatService.cpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(TestChatService, CreateFailMessage_FailMessageCreated) {
	auto chatService = new ChatService();
	std::string message = "{\"type\": \"message\", \"sender\": \"user1\", \"receiver\": \"user2\", \"text\": \"hello\"}";

	std::string reply = chatService->createFailMessage(message);
	json replyJson = json::parse(reply);

	EXPECT_EQ("messageFail", replyJson["type"]);
	EXPECT_EQ("user1", replyJson["sender"]);
	EXPECT_EQ("user2", replyJson["receiver"]);
	EXPECT_EQ("hello", replyJson["text"]);
	EXPECT_EQ("Message was not delivered. user2 leave the chat.", replyJson["reason"]);
}

TEST(TestChatService, CreateUsersList_UsersListCreated) {
	auto chatService = new ChatService();
	std::vector<std::string> users = { "user1", "user2", "user3" };

	std::string reply = chatService->createUsersList(std::make_shared< std::vector<std::string>>(users));
	json replyJson = json::parse(reply);

	EXPECT_EQ("users", replyJson["type"]);
	EXPECT_EQ(3, replyJson["list"].size());
	EXPECT_TRUE(std::find(replyJson["list"].begin(), replyJson["list"].end(), "user1") != replyJson["list"].end());
	EXPECT_TRUE(std::find(replyJson["list"].begin(), replyJson["list"].end(), "user2") != replyJson["list"].end());
	EXPECT_TRUE(std::find(replyJson["list"].begin(), replyJson["list"].end(), "user3") != replyJson["list"].end());
}