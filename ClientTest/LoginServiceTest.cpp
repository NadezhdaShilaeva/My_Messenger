#include "LoginServiceTest.h"

LoginServiceTest::LoginServiceTest()
    : loginService(new LoginService(this))
    , signalLogIn(loginService, &LoginService::logInUser)
    , signalLogOut(loginService, &LoginService::logOutUser)
    , signalLoggedIn(loginService, &LoginService::loggedIn)
    , signalFailed(loginService, &LoginService::loginFailed)
{}

LoginServiceTest::~LoginServiceTest()
{}

void LoginServiceTest::cleanup()
{
    loginService->logoutUser();

    signalLogIn.clear();
    signalLogOut.clear();
    signalLoggedIn.clear();
    signalFailed.clear();
}

void LoginServiceTest::testCheckCredentials_validCredentials_returnTrue()
{
    bool result = loginService->checkCredentials(username1, password);

    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 0);
    QCOMPARE(signalLogOut.count(), 0);

    QCOMPARE(result, true);
}

void LoginServiceTest::testCheckCredentials_emptyUsername_emitSignalFailedAndReturnFalse()
{
    bool result = loginService->checkCredentials(emptyString, password);

    QCOMPARE(signalFailed.count(), 1);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 0);
    QCOMPARE(signalLogOut.count(), 0);

    QString reason = signalFailed.takeFirst().at(0).toString();
    QCOMPARE(reason, "Username cannot be empty.");

    QCOMPARE(result, false);
}

void LoginServiceTest::testCheckCredentials_reservedUsername_emitSignalFailedAndReturnFalse()
{
    bool result = loginService->checkCredentials(reservedUsername, password);

    QCOMPARE(signalFailed.count(), 1);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 0);
    QCOMPARE(signalLogOut.count(), 0);

    QString reason = signalFailed.takeFirst().at(0).toString();
    QCOMPARE(reason, "Username cannot be Favourites because it is a reserved word.");

    QCOMPARE(result, false);
}

void LoginServiceTest::testCheckCredentials_emptyPassword_emitSignalFailedAndReturnFalse()
{
    bool result = loginService->checkCredentials(username1, emptyString);

    QCOMPARE(signalFailed.count(), 1);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 0);
    QCOMPARE(signalLogOut.count(), 0);

    QString reason = signalFailed.takeFirst().at(0).toString();
    QCOMPARE(reason, "Password cannot be empty.");

    QCOMPARE(result, false);
}

void LoginServiceTest::testLoginUser_validLoginUser_usernameSetted()
{
    loginService->loginUser(username1, password, typeLogin);

    QCOMPARE(signalLogIn.count(), 1);
    QCOMPARE(signalLogOut.count(), 0);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), username1);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testLoginUser_validRegisterUser_usernameSetted()
{
    loginService->loginUser(username1, password, typeRegister);

    QCOMPARE(signalLogIn.count(), 1);
    QCOMPARE(signalLogOut.count(), 0);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), username1);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testLoginUser_invalidCredentials_emitSignalFailedAndLogout()
{
    loginService->loginUser(emptyString, emptyString, typeLogin);

    QCOMPARE(signalFailed.count(), 1);
    QCOMPARE(signalLogOut.count(), 1);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 0);

    QString reason = signalFailed.takeFirst().at(0).toString();
    QCOMPARE(reason, "Username cannot be empty.");

    QCOMPARE(loginService->getUsername(), emptyString);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testLoginUser_doubleLoginUser_setFirstUsername()
{
    loginService->loginUser(username1, password, typeLogin);
    loginService->loginUser(username2, password, typeLogin);

    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 1);
    QCOMPARE(signalLogOut.count(), 0);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), username1);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testProcessMessage_validData_emitSignalLoggedIn()
{
    QJsonObject message;
    message["type"] = typeLogin;
    message["username"] = username1;
    message["success"] = true;

    loginService->loginUser(username1, password, typeLogin);
    loginService->processMessage(message);

    QCOMPARE(signalLoggedIn.count(), 1);
    QCOMPARE(signalLogIn.count(), 1);
    QCOMPARE(signalLogOut.count(), 0);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), username1);
    QVERIFY(loginService->getIsLoggedIn());
}

void LoginServiceTest::testProcessMessage_invalidSuccess_notEmitSignalLoggedIn()
{
    QJsonObject message;
    message["type"] = typeLogin;
    message["username"] = username1;
    message["success"] = 0;

    loginService->loginUser(username1, password, typeLogin);
    loginService->processMessage(message);

    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 1);
    QCOMPARE(signalLogOut.count(), 0);

    QCOMPARE(loginService->getUsername(), username1);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testProcessMessage_successFalse_emitSignalsFailedAndLogOut()
{
    QJsonObject message;
    message["type"] = typeLogin;
    message["username"] = username1;
    message["success"] = false;
    message["reason"] = "Some reason";

    loginService->loginUser(username1, password, typeLogin);
    loginService->processMessage(message);

    QCOMPARE(signalFailed.count(), 1);
    QCOMPARE(signalLogOut.count(), 1);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 1);

    QString reason = signalFailed.takeFirst().at(0).toString();
    QCOMPARE(reason, "Some reason");

    QCOMPARE(loginService->getUsername(), emptyString);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testProcessMessage_invalidUsername_notEmitSignalLoggedIn()
{
    QJsonObject message;
    message["type"] = typeLogin;
    message["username"] = username2;
    message["success"] = true;

    loginService->loginUser(username1, password, typeLogin);
    loginService->processMessage(message);

    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 1);
    QCOMPARE(signalLogOut.count(), 0);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), username1);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testProcessMessage_doubleLogin_loginFirstUsername()
{
    QJsonObject message;
    message["type"] = typeLogin;
    message["username"] = username1;
    message["success"] = true;

    QJsonObject message2;
    message2["type"] = typeLogin;
    message2["username"] = username2;
    message2["success"] = true;

    loginService->loginUser(username1, password, typeLogin);
    loginService->processMessage(message);
    loginService->processMessage(message2);

    QCOMPARE(signalLoggedIn.count(), 1);
    QCOMPARE(signalLogIn.count(), 1);
    QCOMPARE(signalLogOut.count(), 0);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), username1);
    QVERIFY(loginService->getIsLoggedIn());
}

void LoginServiceTest::testLogoutUser_clearUsernameAndEmitSignalLogOut()
{
    loginService->loginUser(username1, password, typeLogin);

    QJsonObject message;
    message["type"] = typeLogin;
    message["username"] = username1;
    message["success"] = true;
    loginService->processMessage(message);

    loginService->logoutUser();

    QCOMPARE(signalLogIn.count(), 1);
    QCOMPARE(signalLoggedIn.count(), 1);
    QCOMPARE(signalLogOut.count(), 1);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), emptyString);
    QVERIFY(!loginService->getIsLoggedIn());
}

//QTEST_MAIN(LoginServiceTest)
