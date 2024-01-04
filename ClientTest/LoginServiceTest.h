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

    void testCheckCredentials_validCredentials_returnTrue();
    void testCheckCredentials_emptyUsername_emitSignalFailedAndReturnFalse();
    void testCheckCredentials_reservedUsername_emitSignalFailedAndReturnFalse();
    void testCheckCredentials_emptyPassword_emitSignalFailedAndReturnFalse();

    void testLoginUser_validLoginUser_usernameSetted();
    void testLoginUser_validRegisterUser_usernameSetted();
    void testLoginUser_invalidCredentials_emitSignalFailedAndLogout();
    void testLoginUser_doubleLoginUser_setFirstUsername();

    void testProcessMessage_validData_emitSignalLoggedIn();
    void testProcessMessage_invalidSuccess_notEmitSignalLoggedIn();
    void testProcessMessage_successFalse_emitSignalsFailedAndLogOut();
    void testProcessMessage_invalidUsername_notEmitSignalLoggedIn();
    void testProcessMessage_doubleLogin_loginFirstUsername();

    void testLogoutUser_clearUsernameAndEmitSignalLogOut();

private:
    LoginService *loginService;

    QSignalSpy signalLogIn;
    QSignalSpy signalLogOut;
    QSignalSpy signalLoggedIn;
    QSignalSpy signalFailed;

    const QString typeLogin = "login";
    const QString typeRegister = "register";

    const QString username1 = "Nadezhda";
    const QString username2 = "Anna";
    const QString reservedUsername = "Favourites";

    const QString password = "123456";
    const QString emptyString = "";
};

#endif // LOGINSERVICETEST_H
