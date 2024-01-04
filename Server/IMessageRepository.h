#pragma once

#include <string>
#include <list>
#include <optional>

#include "Message.h"

class IMessageRepository
{
public:
	virtual std::list<Message> findByReceiver(const User& user) = 0;
	virtual std::list<Message> findBySender(const User& user) = 0;
	virtual std::list<Message> findBySenderOrReceiver(const User& user) = 0;
	virtual void save(const Message& message) = 0;
};