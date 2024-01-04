#include "Message.h"

Message::Message(const User& receiver, const User& sender, const std::string& text, const std::string& time)
	: receiver(receiver), sender(sender), text(text), time(time)
{}

const User& Message::getReceiver() const
{
	return receiver;
}

const User& Message::getSender() const
{
	return sender;
}

const std::string& Message::getText() const
{
	return text;
}

const std::string& Message::getTime() const
{
	return time;
}