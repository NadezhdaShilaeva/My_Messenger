#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <map>

#include "ChatClient.h"
#include "LoginService.h"
#include "ChatService.h"

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
    ChatClient *chatClient;
    LoginService *loginService;
    ChatService *chatService;
    QStandardItemModel* usersModel;
    QSortFilterProxyModel *proxyModel;
    std::map<QString, QStandardItemModel*> chatModels;

private slots:
    void login();
    void logout();
    void onLoggedIn();
    void onLoginFailed(QString reason);

    void onUsersListReceived(const QJsonArray& usersArray);
    void onMessageReceived(QString sender, QString text);
    void onMessageFailed(QString receiver, QString text, QString reason);
    void changeUser(const QModelIndex &userIndex);
    void sendMessage();

    void changePageToUsers();

    void onDisconnectedFromServer();
    void onError(QAbstractSocket::SocketError socketError);

private:
    void printMessage(QStandardItemModel* currentModel, QString text, bool self);
};
#endif // MAINWINDOW_H
