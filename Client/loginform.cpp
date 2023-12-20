#include "loginform.h"
#include "ui_loginform.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

LoginForm::LoginForm(QWidget *parent, ChatClient *chatClient) :
    QWidget(parent),
    ui(new Ui::LoginForm),
    chatClient(chatClient)
{
    ui->setupUi(this);

    connect(ui->enterButton, &QPushButton::clicked, this, &LoginForm::connectToServer);
    connect(chatClient, &ChatClient::connected, this, &LoginForm::onConnected);
    connect(chatClient, &ChatClient::loggedIn, this, &LoginForm::onLoggedIn);
    connect(chatClient, &ChatClient::loginError, this, &LoginForm::onLoginFailed);
    connect(chatClient, &ChatClient::error, this, &LoginForm::onError);
    connect(chatClient, &ChatClient::disconnected, this, &LoginForm::onError);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::connectToServer()
{
    chatClient->connectToServer();
}

void LoginForm::onConnected()
{
    QString username = ui->usernameEdit->text();

    if (username.isEmpty())
        return chatClient->disconnectFromServer();;

    login(username);
}

void LoginForm::login(QString username)
{
    chatClient->login(username);
}

void LoginForm::onLoggedIn()
{
    this->hide();
}

void LoginForm::onLoginFailed(QString reason)
{
    ui->usernameEdit->clear();

    QMessageBox::warning(this, "Failed authorization!", reason + " Please, try again.");
}

void LoginForm::onError()
{
    this->hide();
}

