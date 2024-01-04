#pragma once

#include "gtest/gtest.h"
#include "../Server/User.cpp"
#include "../Server/InMemoryUserRepository.cpp"
#include "../Server/LoginService.cpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(TestLoginService, UsernameEmpty_RegisterFail)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto loginService = new LoginService(userRepository);

	std::string username = "";
	std::string password = "123456";

	std::string reply = loginService->registerUser(username, password);
	json replyJson = json::parse(reply);

	EXPECT_EQ("register", replyJson["type"]);
	EXPECT_FALSE(replyJson["success"]);
	EXPECT_EQ("Username must contain at least one symbol.", replyJson["reason"]);
}

TEST(TestLoginService, PasswordEmpty_RegisterFail)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto loginService = new LoginService(userRepository);

	std::string username = "User1";
	std::string password = "";

	std::string reply = loginService->registerUser(username, password);
	json replyJson = json::parse(reply);

	EXPECT_EQ("register", replyJson["type"]);
	EXPECT_FALSE(replyJson["success"]);
	EXPECT_EQ("Password must contain at least one symbol.", replyJson["reason"]);
}

TEST(TestLoginService, UsernameExists_RegisterFail)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto loginService = new LoginService(userRepository);
	userRepository->save(User("user1", "123456"));

	std::string username = "user1";
	std::string password = "1234567";

	std::string reply = loginService->registerUser(username, password);
	json replyJson = json::parse(reply);

	EXPECT_EQ("register", replyJson["type"]);
	EXPECT_FALSE(replyJson["success"]);
	EXPECT_EQ("Username already exists.", replyJson["reason"]);
}

TEST(TestLoginService, UserValid_RegisterSuccess)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto loginService = new LoginService(userRepository);
	User user1 = User("user1", "123456");
	userRepository->save(user1);

	std::string username = "user2";
	std::string password = "1234567";

	std::string reply = loginService->registerUser(username, password);
	json replyJson = json::parse(reply);

	EXPECT_EQ("register", replyJson["type"]);
	EXPECT_TRUE(replyJson["success"]);
	EXPECT_TRUE(replyJson["reason"].empty());

	auto& users = userRepository->findAll();
	EXPECT_EQ(2, users.size());
	EXPECT_EQ(user1, users.front());
	EXPECT_EQ(User(username, password), users.back());
}

TEST(TestLoginService, UsernameNotExists_LoginFail)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto loginService = new LoginService(userRepository);

	std::string username = "user1";
	std::string password = "123456";

	std::string reply = loginService->loginUser(username, password);
	json replyJson = json::parse(reply);

	EXPECT_EQ("login", replyJson["type"]);
	EXPECT_FALSE(replyJson["success"]);
	EXPECT_EQ("Wrong username or password.", replyJson["reason"]);
}

TEST(TestLoginService, WrongPassword_LoginFail)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto loginService = new LoginService(userRepository);
	User user1 = User("user1", "123456");
	userRepository->save(user1);

	std::string username = "user1";
	std::string password = "1234567";

	std::string reply = loginService->loginUser(username, password);
	json replyJson = json::parse(reply);

	EXPECT_EQ("login", replyJson["type"]);
	EXPECT_FALSE(replyJson["success"]);
	EXPECT_EQ("Wrong username or password.", replyJson["reason"]);
}

TEST(TestLoginService, UserExists_LoginSuccess)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto loginService = new LoginService(userRepository);
	User user1 = User("user1", "123456");
	userRepository->save(user1);

	std::string username = "user1";
	std::string password = "123456";

	std::string reply = loginService->loginUser(username, password);
	json replyJson = json::parse(reply);

	EXPECT_EQ("login", replyJson["type"]);
	EXPECT_TRUE(replyJson["success"]);
	EXPECT_TRUE(replyJson["reason"].empty());
}