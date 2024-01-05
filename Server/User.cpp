#include "User.h"

User::User(const std::string& username, const std::string& password, const std::string& salt)
	: username(username), password(password), salt(salt)
{}

bool User::operator==(const User& other) const
{
	return this->username == other.username && this->password == other.password && this->salt == other.salt;
}

std::string User::getUsername() const
{
	return username;
}

std::string User::getPassword() const
{
	return password;
}

std::string User::getSalt() const
{
	return salt;
}