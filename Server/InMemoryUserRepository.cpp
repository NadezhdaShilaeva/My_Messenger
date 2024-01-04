#include "InMemoryUserRepository.h"

InMemoryUserRepository::InMemoryUserRepository()
{}

const std::list<User>& InMemoryUserRepository::findAll()
{
	return users;
}

std::optional<User> InMemoryUserRepository::findByUsername(const std::string& username)
{
	for (auto& user : users)
	{
		if (user.getUsername() == username)
		{
			return user;
		}
	}

	return std::nullopt;
}

std::optional<User> InMemoryUserRepository::findByUsernameAndPassword(const std::string& username, const std::string& password)
{
	for (auto& user : users)
	{
		if (user.getUsername() == username && user.getPassword() == password)
		{
			return user;
		}
	}

	return std::nullopt;
}

void InMemoryUserRepository::save(const User& user)
{
	users.push_back(user);
}