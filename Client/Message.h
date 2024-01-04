#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QTime>

class Message
{
public:
    Message();
    explicit Message(QString sender, QString receiver, QString text, QTime time);

private:
    QString sender;
    QString receiver;
    QString text;
    QTime time;

public:
    QString getSender() const;
    QString getReceiver() const;
    QString getText() const;
    QTime getTime() const;
};

#endif // MESSAGE_H
