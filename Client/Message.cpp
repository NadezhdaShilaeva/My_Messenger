#include "Message.h"

Message::Message()
{}

Message::Message(QString sender, QString receiver, QString text, QTime time)
    : sender(sender), receiver(receiver), text(text), time(time)
{}

QString Message::getSender() const
{
    return sender;
}

QString Message::getReceiver() const
{
    return receiver;
}

QString Message::getText() const
{
    return text;
}

QTime Message::getTime() const
{
    return time;
}
