#pragma once

#include "gtest/gtest.h"
#include "../Server/User.cpp"
#include "../Server/InMemoryUserRepository.cpp"
#include "../Server/LoginService.cpp"
#include "MockEncoder.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(TestLoginService, UsernameEmpty_RegisterFail)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto encoder = std::make_shared<MockEncoder>();
	auto loginService = new LoginService(userRepository, encoder);

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
	auto encoder = std::make_shared<MockEncoder>();
	auto loginService = new LoginService(userRepository, encoder);

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
	auto encoder = std::make_shared<MockEncoder>();
	auto loginService = new LoginService(userRepository, encoder);
	userRepository->save(User("user1", "123456", encoder->generateSalt()));

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
	auto encoder = std::make_shared<MockEncoder>();
	auto loginService = new LoginService(userRepository, encoder);
	std::string salt = encoder->generateSalt();
	std::string hashPassword = encoder->sha1("123456", salt);
	User user1 = User("user1", hashPassword, salt);
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
	EXPECT_EQ(User(username, encoder->sha1(password, salt), salt), users.back());
}

TEST(TestLoginService, UsernameNotExists_LoginFail)
{
	auto userRepository = std::make_shared<InMemoryUserRepository>();
	auto encoder = std::make_shared<MockEncoder>();
	auto loginService = new LoginService(userRepository, encoder);

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
	auto encoder = std::make_shared<MockEncoder>();
	auto loginService = new LoginService(userRepository, encoder);
	User user1 = User("user1", "123456", encoder->generateSalt());
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
	auto encoder = std::make_shared<MockEncoder>();
	auto loginService = new LoginService(userRepository, encoder);
	std::string salt = encoder->generateSalt();
	std::string hashPassword = encoder->sha1("123456", salt);
	User user1 = User("user1", hashPassword, salt);
	userRepository->save(user1);

	std::string username = "user1";
	std::string password = "123456";

	std::string reply = loginService->loginUser(username, password);
	json replyJson = json::parse(reply);

	EXPECT_EQ("login", replyJson["type"]);
	EXPECT_TRUE(replyJson["success"]);
	EXPECT_TRUE(replyJson["reason"].empty());
}