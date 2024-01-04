#pragma once

#include "IUserRepository.h"

class InMemoryUserRepository : public IUserRepository
{
public:
	explicit InMemoryUserRepository();

	const std::list<User>& findAll();
	std::optional<User> findByUsername(const std::string& username);
	std::optional<User> findByUsernameAndPassword(const std::string& username, const std::string& password);
	void save(const User& user);

private:
	std::list<User> users;
};