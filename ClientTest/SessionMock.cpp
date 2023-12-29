#include "SessionMock.h"

SessionMock::SessionMock(QObject *parent)
    :ISession(parent)
{}

void SessionMock::createSession()
{
    return;
}
