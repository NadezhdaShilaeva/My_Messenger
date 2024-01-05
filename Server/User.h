#pragma once

#include <string>

class User
{
private:
	std::string username;
	std::string password;
	std::string salt;

public:
	explicit User(const std::string& username, const std::string& password, const std::string& salt);
	bool operator==(const User& other) const;

	std::string getUsername() const;
	std::string getPassword() const;
	std::string getSalt() const;
};