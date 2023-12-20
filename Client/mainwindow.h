#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <map>
#include "chatclient.h"
#include "loginform.h"

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
    LoginForm *loginForm;
    QString username;
    std::map<QString, QStandardItemModel*> chatModels;

private slots:
    void login();
    void onLoggedIn(QString username);
    void onMessageReceived(QString sender, QString text);
    void sendMessage();
    void changeUser(QString currentUser);
    void onDisconnectedFromServer();
    void onUserJoined(QString username);
    void onUserLeft(QString username);
    void onError(QAbstractSocket::SocketError socketError);
};
#endif // MAINWINDOW_H
