#include "InMemoryMessageRepository.h"

InMemoryMessageRepository::InMemoryMessageRepository()
{}

std::list<Message> InMemoryMessageRepository::findByReceiver(const User& user)
{
	std::list<Message> result;

	for (auto& message : messages)
	{
		if (message.getReceiver() == user)
		{
			result.push_back(message);
		}
	}

	return result;
}

std::list<Message> InMemoryMessageRepository::findBySender(const User& user)
{
	std::list<Message> result;

	for (auto& message : messages)
	{
		if (message.getSender() == user)
		{
			result.push_back(message);
		}
	}

	return result;
}

std::list<Message> InMemoryMessageRepository::findBySenderOrReceiver(const User& user)
{
	std::list<Message> result;

	for (auto& message : messages)
	{
		if (message.getSender() == user || message.getReceiver() == user)
		{
			result.push_back(message);
		}
	}

	return result;
}

void InMemoryMessageRepository::save(const Message& message)
{
	messages.push_back(message);
}