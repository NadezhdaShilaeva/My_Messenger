#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "LoginService.h"
#include "Session.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QTime>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , loginService(new LoginService(this))
    , chatService(new ChatService(this))
    , session(new Session(loginService, chatService, this))
    , usersModel(new QStandardItemModel(this))
    , proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    proxyModel->setSourceModel(usersModel);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    connect(ui->findUserEdit, SIGNAL(textChanged(QString)), proxyModel, SLOT(setFilterRegExp(QString)));
    ui->usersListView->setModel(proxyModel);

    connect(loginService, &LoginService::disconnected, this, &MainWindow::onDisconnectedFromServer);
    connect(loginService, &LoginService::error, this, &MainWindow::onError);
    connect(loginService, &LoginService::loggedIn, this, &MainWindow::onLoggedIn);
    connect(loginService, &LoginService::loginFailed, this, &MainWindow::onLoginFailed);
    connect(chatService, &ChatService::usersListReceived, this, &MainWindow::onUsersListReceived);
    connect(chatService, &ChatService::messageReceived, this, &MainWindow::onMessageReceived);
    connect(chatService, &ChatService::messageFailed, this, &MainWindow::onMessageFailed);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::login);
    connect(ui->logoutButton, &QPushButton::clicked, this, &MainWindow::logout);
    connect(ui->logoutButton2, &QPushButton::clicked, this, &MainWindow::logout);
    connect(ui->usersListView, &QListView::clicked, this, &MainWindow::changeUser);
    connect(ui->returnButton, &QPushButton::clicked, this, &MainWindow::changePageToUsers);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendMessage);
    connect(ui->messageEdit, &QLineEdit::returnPressed, this, &MainWindow::sendMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login()
{
    QString username = ui->usernameEdit->text();

    ui->loginButton->setEnabled(false);

    loginService->loginUser(username, session);
}

void MainWindow::logout()
{
    loginService->logoutUser();

    chatModels.clear();
    ui->usernameEdit->clear();
    ui->loginButton->setEnabled(true);
    this->setWindowTitle("My messenger");
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::onLoggedIn()
{
    ui->usernameEdit->clear();
    ui->loginButton->setEnabled(true);
    this->setWindowTitle("My messenger - " + loginService->getUsername());
    changePageToUsers();
}

void MainWindow::onLoginFailed(QString reason)
{
    ui->usernameEdit->clear();
    ui->loginButton->setEnabled(true);
    QMessageBox::warning(this, "Failed authorization!", reason + " Please, try again.");
}

void MainWindow::onUsersListReceived(const QJsonArray& usersArray)
{
    usersModel->clear();
    usersModel->insertColumn(0);

    int newRow = 0;
    usersModel->insertRow(newRow);
    usersModel->setData(usersModel->index(newRow, 0), "Favourites");
    usersModel->setData(usersModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
    QFont font;
    font.setBold(700);
    usersModel->setData(usersModel->index(newRow, 0), font, Qt::FontRole);
    newRow++;

    for (auto& user: chatModels)
    {
        if (user.first == "Favourites")
            continue;

        usersModel->insertRow(newRow);

        usersModel->setData(usersModel->index(newRow, 0), user.first);
        usersModel->setData(usersModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
        newRow++;
    }
    for (int i = 0; i < usersArray.size(); ++i)
    {
        QString newUser = usersArray.at(i).toString();
        if (chatModels.count(newUser) or newUser == loginService->getUsername())
            continue;

        usersModel->insertRow(newRow);

        usersModel->setData(usersModel->index(newRow, 0), newUser);
        usersModel->setData(usersModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
        newRow++;
    }
}

void MainWindow::sendMessage()
{
    QString receiver = ui->usernameLabel->text();
    QString text = ui->messageEdit->text();

    if (ui->usernameLabel->text() != "Favourites")
    {
        chatService->sendTextMessage(text, loginService->getUsername(), receiver);
    }

    QStandardItemModel *currentModel;
    if (chatModels.count(receiver))
    {
        currentModel = chatModels[receiver];
    }
    else
    {
        currentModel = chatModels[receiver] = new QStandardItemModel();
        currentModel->insertColumn(0);
    }

    printMessage(currentModel, text, true);

    ui->messageEdit->clear();
    ui->chatView->setModel(currentModel);
    ui->chatView->scrollToBottom();
}

void MainWindow::onMessageReceived(QString sender, QString text)
{
    QStandardItemModel *currentModel;
    if (chatModels.count(sender))
    {
        currentModel = chatModels[sender];
    }
    else
    {
        currentModel = chatModels[sender] = new QStandardItemModel();
        currentModel->insertColumn(0);
    }

    printMessage(currentModel, text, false);

    if (ui->usernameLabel->text() == sender)
    {
        ui->chatView->setModel(currentModel);
        ui->chatView->scrollToBottom();
    }
}

void MainWindow::onMessageFailed(QString receiver, QString text, QString reason)
{
    QStandardItemModel *currentModel = chatModels[receiver];
    QModelIndex failedIdx = currentModel->findItems(text).constLast()->index();

    currentModel->setData(currentModel->index(failedIdx.row() + 1, 0), reason);
    currentModel->setData(currentModel->index(failedIdx.row() + 1, 0), QBrush(Qt::red), Qt::ForegroundRole);

    if (ui->usernameLabel->text() == receiver)
    {
        ui->chatView->setModel(currentModel);
        ui->chatView->scrollToBottom();
    }
}

void MainWindow::printMessage(QStandardItemModel* currentModel, QString text, bool self)
{
    int alignment;
    if (self)
    {
        alignment = int(Qt::AlignRight | Qt::AlignVCenter);
    }
    else
    {
        alignment = int(Qt::AlignLeft | Qt::AlignVCenter);
    }

    int newRow = currentModel->rowCount();
    currentModel->insertRows(newRow, 2);
    QFont font;
    font.setFamily("Calibri");
    font.setPixelSize(18);
    currentModel->setData(currentModel->index(newRow, 0), text);
    currentModel->setData(currentModel->index(newRow, 0), alignment, Qt::TextAlignmentRole);
    currentModel->setData(currentModel->index(newRow, 0), font, Qt::FontRole);

    newRow++;
    font.setPixelSize(12);
    currentModel->setData(currentModel->index(newRow, 0), QTime::currentTime().toString("hh:mm"));
    currentModel->setData(currentModel->index(newRow, 0), alignment, Qt::TextAlignmentRole);
    currentModel->setData(currentModel->index(newRow, 0), font, Qt::FontRole);
}

void MainWindow::changePageToUsers()
{
    chatService->sendGetUsersRequest();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::changeUser(const QModelIndex& userIndex)
{
    QString currentUser = usersModel->itemFromIndex(proxyModel->mapToSource(userIndex))->text();
    ui->usernameLabel->setText(currentUser);

    QStandardItemModel *currentModel;
    if (chatModels.count(currentUser))
    {
        currentModel = chatModels[currentUser];
    }
    else
    {
        currentModel = chatModels[currentUser] = new QStandardItemModel();
        currentModel->insertColumn(0);
    }

    ui->chatView->setModel(currentModel);
    ui->chatView->scrollToBottom();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::onDisconnectedFromServer()
{
    if (ui->stackedWidget->currentIndex() != 0)
    {
        logout();
        QMessageBox::warning(this, "Disconnected", "The host terminated the connection.");
    }
}

void MainWindow::onError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
        return;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
        break;
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::critical(this, tr("Error"), tr("An unknown error occurred"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy communication failed"));
        break;
    case QAbstractSocket::TemporaryError:
    case QAbstractSocket::OperationError:
        QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
        return;
    default:
        Q_UNREACHABLE();
    }

    logout();
}

