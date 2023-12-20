#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include "chatclient.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr, ChatClient *chatClient = nullptr);
    ~LoginForm();

private:
    Ui::LoginForm *ui;
    ChatClient *chatClient;

private slots:
    void onConnected();
    void onLoggedIn();
    void onLoginFailed(QString reason);
    void onError();

public:
    void connectToServer();

private:
    void login(QString username);
};

#endif // LOGINFORM_H
