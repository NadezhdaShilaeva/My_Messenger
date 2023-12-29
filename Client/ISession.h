#ifndef ISESSION_H
#define ISESSION_H

#include <QObject>

class ISession : public QObject
{
    Q_OBJECT

public:
    ISession(QObject *parent = nullptr)
        : QObject(parent)
    {}

    virtual void createSession() = 0;
};

#endif // ISESSION_H
