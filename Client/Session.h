#ifndef SESSION_H
#define SESSION_H

#include "ISession.h"
#include "LoginService.h"
#include "ChatService.h"

#include <QObject>

class Session : public ISession
{
    Q_OBJECT

public:
    explicit Session(LoginService *loginService, ChatService *chatService, QObject *parent = nullptr);

    void createSession();

private:
    LoginService *loginService;
    ChatService *chatService;
};

#endif // SESSION_H
