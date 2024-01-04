#pragma once

#include <string>
#include <list>
#include <optional>

#include "User.h"

class IUserRepository
{
public:
	virtual const std::list<User>& findAll() = 0;
	virtual std::optional<User> findByUsername(const std::string& username) = 0;
	virtual std::optional<User> findByUsernameAndPassword(const std::string& username, const std::string& password) = 0;
	virtual void save(const User& user) = 0;
};