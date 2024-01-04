#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "LoginService.h"
#include "Session.h"

#include <QInputDialog>
#include <QMessageBox>
#include <string>

const QString FAVOURITES = "Favourites";

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

    connect(loginService, &LoginService::connectedToServer, this, &MainWindow::login);
    connect(loginService, &LoginService::disconnected, this, &MainWindow::onDisconnectedFromServer);
    connect(loginService, &LoginService::error, this, &MainWindow::onError);
    connect(loginService, &LoginService::loggedIn, this, &MainWindow::onLoggedIn);
    connect(loginService, &LoginService::loginFailed, this, &MainWindow::onLoginFailed);
    connect(chatService, &ChatService::chatMessagesReceived, this, &MainWindow::onChatMessagesReceived);
    connect(chatService, &ChatService::usersListReceived, this, &MainWindow::onUsersListReceived);
    connect(chatService, &ChatService::messageReceived, this, &MainWindow::onMessageReceived);
    connect(chatService, &ChatService::messageFailed, this, &MainWindow::onMessageFailed);

    connect(ui->registerButton, &QPushButton::clicked, this, &MainWindow::onRegister);
    connect(ui->registerLabelButton, &QPushButton::clicked, this, &MainWindow::changePageToRegister);
    connect(ui->loginLabelButton, &QPushButton::clicked, this, &MainWindow::changePageToLogin);
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::onLogin);
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

void MainWindow::changePageToRegister()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::changePageToLogin()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::onRegister()
{
    QString username = ui->usernameRegEdit->text();
    QString password = ui->passwordRegEdit->text();

    if (!loginService->checkCredentials(username, password))
        return;

    ui->usernameRegEdit->setEnabled(false);
    ui->passwordRegEdit->setEnabled(false);
    ui->registerButton->setEnabled(false);
    ui->loginLabelButton->setEnabled(false);

    session->createSession();
}

void MainWindow::onLogin()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    if (!loginService->checkCredentials(username, password))
        return;

    ui->usernameEdit->setEnabled(false);
    ui->passwordEdit->setEnabled(false);
    ui->loginButton->setEnabled(false);
    ui->registerLabelButton->setEnabled(false);

    session->createSession();
}

void MainWindow::login()
{
    if (ui->stackedWidget->currentIndex() == 3)
    {
        QString username = ui->usernameRegEdit->text();
        QString password = ui->passwordRegEdit->text();

        ui->registerButton->setEnabled(false);

        loginService->loginUser(username, password, "register");
    }

    if (ui->stackedWidget->currentIndex() == 0)
    {
        QString username = ui->usernameEdit->text();
        QString password = ui->passwordEdit->text();

        ui->loginButton->setEnabled(false);

        loginService->loginUser(username, password, "login");
    }
}

void MainWindow::setInitialWidgets()
{
    ui->usernameEdit->setEnabled(true);
    ui->passwordEdit->setEnabled(true);
    ui->usernameRegEdit->setEnabled(true);
    ui->passwordRegEdit->setEnabled(true);
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
    ui->usernameRegEdit->clear();
    ui->passwordRegEdit->clear();
    ui->loginButton->setEnabled(true);
    ui->registerButton->setEnabled(true);
    ui->loginLabelButton->setEnabled(true);
    ui->registerLabelButton->setEnabled(true);
}

void MainWindow::logout()
{
    loginService->logoutUser();

    chatModels.clear();
    setInitialWidgets();

    this->setWindowTitle("My messenger");

    if (ui->stackedWidget->currentIndex() != 0 and ui->stackedWidget->currentIndex() != 3)
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::onLoggedIn()
{
    setInitialWidgets();

    this->setWindowTitle("My messenger - " + loginService->getUsername());
    changePageToUsers();
}

void MainWindow::onLoginFailed(QString reason)
{
    qDebug() << reason;
    setInitialWidgets();

    QMessageBox::warning(this, "Failed authorization!", reason + " Please, try again.");
}

void MainWindow::onUsersListReceived(const QVector<QString>& usersArray)
{
    usersModel->clear();
    usersModel->insertColumn(0);

    QIcon favIcon = QIcon(":/icons/circle-bookmark.png");
    QStandardItem* item = new QStandardItem(favIcon, FAVOURITES);
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    usersModel->appendRow(item);

    QFont font;
    font.setBold(700);
    item->setFont(font);

    QIcon userIcon = QIcon(":/icons/circle-user.png");

    for (auto& user: chatModels)
    {
        if (user.first == loginService->getUsername())
            continue;

        QStandardItem* item = new QStandardItem(userIcon, user.first);
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        usersModel->appendRow(item);
    }


    for (auto& newUser : usersArray)
    {
        if (chatModels.count(newUser) or newUser == loginService->getUsername())
            continue;

        QStandardItem* item = new QStandardItem(userIcon, newUser);
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        usersModel->appendRow(item);
    }
}

void MainWindow::sendMessage()
{
    QString receiver = ui->usernameLabel->text();
    QString text = ui->messageEdit->text();
    QTime time = QTime::currentTime();

    if (receiver == FAVOURITES)
    {
        receiver = loginService->getUsername();
    }

    chatService->sendTextMessage(text, loginService->getUsername(), receiver, time);
    ui->messageEdit->clear();

    if (receiver == loginService->getUsername())
        return;

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

    printMessage(currentModel, text, time, true);

    ui->chatView->setModel(currentModel);
    ui->chatView->scrollToBottom();
}

void MainWindow::onMessageReceived(QString sender, QString text, QTime time)
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

    printMessage(currentModel, text, time, sender == loginService->getUsername());

    if (ui->usernameLabel->text() == (sender == loginService->getUsername() ? FAVOURITES : sender))
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

void MainWindow::printMessage(QStandardItemModel* currentModel, QString text, QTime time, bool self)
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
    currentModel->setData(currentModel->index(newRow, 0), time.toString("hh:mm"));
    currentModel->setData(currentModel->index(newRow, 0), alignment, Qt::TextAlignmentRole);
    currentModel->setData(currentModel->index(newRow, 0), font, Qt::FontRole);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (ui->stackedWidget->currentIndex() == 1 and event->key() == Qt::Key_F5)
    {
        chatService->sendGetUsersRequest();
    }
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
    ui->messageEdit->clear();

    if (currentUser == FAVOURITES)
    {
        currentUser = loginService->getUsername();
    }

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

void MainWindow::onChatMessagesReceived(const QVector<Message>& messagesArray)
{
    for (auto& message : messagesArray)
    {
        QString receiver = message.getReceiver();
        QString sender = message.getSender();
        QString text = message.getText();
        QTime time = message.getTime();

        QString secondUser = sender == loginService->getUsername() ? receiver : sender;

        QStandardItemModel *currentModel;
        if (chatModels.count(secondUser))
        {
            currentModel = chatModels[secondUser];
        }
        else
        {
            currentModel = chatModels[secondUser] = new QStandardItemModel();
            currentModel->insertColumn(0);
        }

        printMessage(currentModel, text, time, secondUser == receiver);
    }
}

void MainWindow::onDisconnectedFromServer()
{
    if (ui->stackedWidget->currentIndex() != 0 and ui->stackedWidget->currentIndex() != 3)
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

