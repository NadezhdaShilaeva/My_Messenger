#pragma once

#include "gtest/gtest.h"
#include "../Server/LoginService.cpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(TestLoginService, UsernameEmpty_LoginFail) {
	auto loginService = new LoginService();
	std::vector<std::string> users = {};
	std::string newUser = "";

	std::string reply = loginService->loginClient(std::make_shared< std::vector<std::string>>(users), newUser);
	json replyJson = json::parse(reply);

	EXPECT_EQ("login", replyJson["type"]);
	EXPECT_FALSE(replyJson["success"]);
	EXPECT_EQ("Username must contain at least one symbol.", replyJson["reason"]);
}

TEST(TestLoginService, UsernameExists_LoginFail) {
	auto loginService = new LoginService();
	std::vector<std::string> users = {"user1", "user2", "user3"};
	std::string newUser = "user3";

	std::string reply = loginService->loginClient(std::make_shared< std::vector<std::string>>(users), newUser);
	json replyJson = json::parse(reply);

	EXPECT_EQ("login", replyJson["type"]);
	EXPECT_FALSE(replyJson["success"]);
	EXPECT_EQ("Username already exists.", replyJson["reason"]);
}

TEST(TestLoginService, UsernameValid_LoginSuccess) {
	auto loginService = new LoginService();
	std::vector<std::string> users = { "user1", "user2", "user3" };
	std::string newUser = "user4";

	std::string reply = loginService->loginClient(std::make_shared< std::vector<std::string>>(users), newUser);
	json replyJson = json::parse(reply);

	EXPECT_EQ("login", replyJson["type"]);
	EXPECT_TRUE(replyJson["success"]);
	EXPECT_TRUE(replyJson["reason"].empty());
}