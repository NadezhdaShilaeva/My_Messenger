#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QKeyEvent>
#include <QTime>
#include <map>

#include "ChatClient.h"
#include "LoginService.h"
#include "ChatService.h"
#include "ISession.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoginService *loginService;
    ChatService *chatService;
    ISession * session;
    QStandardItemModel* usersModel;
    QSortFilterProxyModel *proxyModel;
    std::map<QString, QStandardItemModel*> chatModels;

private slots:
    void onRegister();
    void onLogin();

    void login();
    void logout();
    void onLoggedIn();
    void onLoginFailed(QString reason);

    void onChatMessagesReceived(const QVector<Message>& messagesArray);
    void onUsersListReceived(const QVector<QString>& usersArray);
    void onMessageReceived(QString sender, QString text, QTime time);
    void onMessageFailed(QString receiver, QString text, QString reason);
    void changeUser(const QModelIndex &userIndex);
    void sendMessage();

    void changePageToRegister();
    void changePageToLogin();
    void changePageToUsers();

    void onDisconnectedFromServer();
    void onError(QAbstractSocket::SocketError socketError);

private:
    void keyPressEvent(QKeyEvent *event) override;
    void setInitialWidgets();
    void printMessage(QStandardItemModel* currentModel, QString text, QTime time, bool self);
};
#endif // MAINWINDOW_H
