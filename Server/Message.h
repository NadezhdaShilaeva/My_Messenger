#pragma once

#include "User.h"

class Message
{
private:
	User receiver;
	User sender;
	std::string text;
	std::string time;

public:
	explicit Message(const User& receiver, const User& sender, const std::string& text, const std::string& time);

	const User& getReceiver() const;
	const User& getSender() const;
	const std::string& getText() const;
	const std::string& getTime() const;
};