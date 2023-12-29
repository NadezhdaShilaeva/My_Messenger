#ifndef LOGINSERVICETEST_H
#define LOGINSERVICETEST_H

#include <QtTest>
#include <QCoreApplication>

#include "LoginService.h"
#include "ISession.h"

class LoginServiceTest : public QObject
{
    Q_OBJECT

public:
    LoginServiceTest();
    ~LoginServiceTest();

private slots:
    void cleanup();

    void testLoginUser_validUsername_usernameSetted();
    void testLoginUser_emptyUsername_emitSignalFailed();
    void testLoginUser_reservedUsername_emitSignalFaailed();
    void testLoginUser_doubleLoginUser_setFirstUsername();

    void testLogin_validUsername_emitSignalLogin();
    void testLogin_emptyUsername_notEmitSignalLogIn();

    void testProcessMessage_validData_emitSignalLoggedIn();
    void testProcessMessage_invalidSuccess_notEmitSignals();
    void testProcessMessage_successFalse_emitSignalsFailedAndLogOut();
    void testProcessMessage_invalidUsername_notEmitSignals();
    void testProcessMessage_doubleLogin_loginFirstUsername();

    void testLogoutUser_clearUsernameAndEmitSignalLogOut();

private:
    LoginService *loginService;
    ISession *session;

    QSignalSpy signalLogIn;
    QSignalSpy signalLogOut;
    QSignalSpy signalLoggedIn;
    QSignalSpy signalFailed;

    const QString typeLogin = "login";

    const QString username1 = "Nadezhda";
    const QString username2 = "Anna";
    const QString emptyUsername = "";
};

#endif // LOGINSERVICETEST_H
