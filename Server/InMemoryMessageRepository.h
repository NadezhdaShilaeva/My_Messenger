#pragma once

#include "IMessageRepository.h"

class InMemoryMessageRepository : public IMessageRepository
{
public:
	explicit InMemoryMessageRepository();

	std::list<Message> findByReceiver(const User& user);
	std::list<Message> findBySender(const User& user);
	std::list<Message> findBySenderOrReceiver(const User& user);
	void save(const Message& message);

private:
	std::list<Message> messages;
};