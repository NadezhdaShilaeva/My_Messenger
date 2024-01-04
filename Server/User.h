#pragma once

#include <string>

class User
{
private:
	std::string username;
	std::string password;

public:
	explicit User(const std::string& username, const std::string& password);
	bool operator==(const User& other) const;

	std::string getUsername() const;
	std::string getPassword() const;
};