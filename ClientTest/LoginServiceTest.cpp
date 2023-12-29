#include "LoginServiceTest.h"
#include "SessionMock.h"

LoginServiceTest::LoginServiceTest()
    : loginService(new LoginService(this))
    , session(new SessionMock(this))
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

void LoginServiceTest::testLoginUser_validUsername_usernameSetted()
{
    loginService->loginUser(username1, session);

    QCOMPARE(signalLogIn.count(), 0);
    QCOMPARE(signalLogOut.count(), 0);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), username1);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testLoginUser_emptyUsername_emitSignalFailed()
{
    loginService->loginUser(emptyUsername, session);

    QCOMPARE(signalFailed.count(), 1);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 0);
    QCOMPARE(signalLogOut.count(), 0);

    QString reason = signalFailed.takeFirst().at(0).toString();
    QCOMPARE(reason, "Username cannot be empty.");

    QCOMPARE(loginService->getUsername(), emptyUsername);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testLoginUser_reservedUsername_emitSignalFaailed()
{
    loginService->loginUser("Favourites", session);

    QCOMPARE(signalFailed.count(), 1);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 0);
    QCOMPARE(signalLogOut.count(), 0);

    QString reason = signalFailed.takeFirst().at(0).toString();
    QCOMPARE(reason, "Username cannot be Favourites because it is a reserved word.");

    QCOMPARE(loginService->getUsername(), emptyUsername);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testLoginUser_doubleLoginUser_setFirstUsername()
{
    loginService->loginUser(username1, session);
    loginService->loginUser(username2, session);

    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 0);
    QCOMPARE(signalLogOut.count(), 0);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), username1);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testLogin_validUsername_emitSignalLogin()
{
    loginService->loginUser(username1, session);
    loginService->login();

    QCOMPARE(signalLogIn.count(), 1);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogOut.count(), 0);
    QCOMPARE(signalFailed.count(), 0);

    QString message = signalLogIn.takeFirst().at(0).toString();
    QJsonObject json = QJsonDocument::fromJson(message.toLocal8Bit()).object();
    QCOMPARE(json.value("type"), typeLogin);
    QCOMPARE(json.value("username"), username1);

    QCOMPARE(loginService->getUsername(), username1);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testLogin_emptyUsername_notEmitSignalLogIn()
{
    loginService->login();

    QCOMPARE(signalLogIn.count(), 0);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogOut.count(), 0);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), emptyUsername);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testProcessMessage_validData_emitSignalLoggedIn()
{
    QJsonObject message;
    message["type"] = typeLogin;
    message["username"] = username1;
    message["success"] = true;

    loginService->loginUser(username1, session);
    loginService->processMessage(message);

    QCOMPARE(signalLoggedIn.count(), 1);
    QCOMPARE(signalLogIn.count(), 0);
    QCOMPARE(signalLogOut.count(), 0);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), username1);
    QVERIFY(loginService->getIsLoggedIn());
}

void LoginServiceTest::testProcessMessage_invalidSuccess_notEmitSignals()
{
    QJsonObject message;
    message["type"] = typeLogin;
    message["username"] = username1;
    message["success"] = 0;

    loginService->loginUser(username1, session);
    loginService->processMessage(message);

    QCOMPARE(signalFailed.count(), 0);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 0);
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

    loginService->loginUser(username1, session);
    loginService->processMessage(message);

    QCOMPARE(signalFailed.count(), 1);
    QCOMPARE(signalLogOut.count(), 1);
    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 0);

    QString reason = signalFailed.takeFirst().at(0).toString();
    QCOMPARE(reason, "Some reason");

    QCOMPARE(loginService->getUsername(), emptyUsername);
    QVERIFY(!loginService->getIsLoggedIn());
}

void LoginServiceTest::testProcessMessage_invalidUsername_notEmitSignals()
{
    QJsonObject message;
    message["type"] = typeLogin;
    message["username"] = username2;
    message["success"] = true;

    loginService->loginUser(username1, session);
    loginService->processMessage(message);

    QCOMPARE(signalLoggedIn.count(), 0);
    QCOMPARE(signalLogIn.count(), 0);
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

    loginService->loginUser(username1, session);
    loginService->processMessage(message);
    loginService->processMessage(message2);

    QCOMPARE(signalLoggedIn.count(), 1);
    QCOMPARE(signalLogIn.count(), 0);
    QCOMPARE(signalLogOut.count(), 0);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), username1);
    QVERIFY(loginService->getIsLoggedIn());
}

void LoginServiceTest::testLogoutUser_clearUsernameAndEmitSignalLogOut()
{
    loginService->loginUser(username1, session);

    QJsonObject message;
    message["type"] = typeLogin;
    message["username"] = username1;
    message["success"] = true;
    loginService->processMessage(message);

    loginService->logoutUser();

    QCOMPARE(signalLogIn.count(), 0);
    QCOMPARE(signalLoggedIn.count(), 1);
    QCOMPARE(signalLogOut.count(), 1);
    QCOMPARE(signalFailed.count(), 0);

    QCOMPARE(loginService->getUsername(), emptyUsername);
    QVERIFY(!loginService->getIsLoggedIn());
}

//QTEST_MAIN(LoginServiceTest)
