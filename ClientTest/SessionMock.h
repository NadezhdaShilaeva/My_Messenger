#ifndef SESSIONMOC_H
#define SESSIONMOC_H

#include <QObject>

#include "ISession.h"

class SessionMock : public ISession
{
    Q_OBJECT

public:
    SessionMock(QObject *parent = nullptr);

    void createSession();
};

#endif // SESSIONMOC_H
