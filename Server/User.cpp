#include "User.h"

User::User(const std::string& username, const std::string& password)
	: username(username), password(password)
{}

bool User::operator==(const User& other) const
{
	return this->username == other.username && this->password == other.password;
}

std::string User::getUsername() const
{
	return username;
}

std::string User::getPassword() const
{
	return password;
}