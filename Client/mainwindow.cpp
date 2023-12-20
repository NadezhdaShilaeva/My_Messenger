#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginform.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chatClient(new ChatClient())
    , loginForm(new LoginForm(this, chatClient))
{
    ui->setupUi(this);

    connect(chatClient, &ChatClient::loggedIn, this, &MainWindow::onLoggedIn);
    connect(chatClient, &ChatClient::messageReceived, this, &MainWindow::onMessageReceived);
    connect(chatClient, &ChatClient::disconnected, this, &MainWindow::onDisconnectedFromServer);
    connect(chatClient, &ChatClient::error, this, &MainWindow::onError);
    connect(chatClient, &ChatClient::userJoined, this, &MainWindow::onUserJoined);
    connect(chatClient, &ChatClient::userLeft, this, &MainWindow::onUserLeft);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::login);
    //connect(ui->usersBox, &QComboBox::currentIndexChanged, this, &MainWindow::changeUser);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendMessage);
    connect(ui->messageEdit, &QLineEdit::returnPressed, this, &MainWindow::sendMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login()
{
    ui->loginButton->setEnabled(false);

    loginForm->show();
}

void MainWindow::onLoggedIn(QString userName)
{
    ui->sendButton->setEnabled(true);
    ui->messageEdit->setEnabled(true);
    ui->chatView->setEnabled(true);

    this->show();

    username = userName;
}

void MainWindow::sendMessage()
{
    QString receiver = ui->usersBox->currentText();
    chatClient->sendMessage(ui->messageEdit->text(), username, receiver);

    QStandardItemModel *currentModel = chatModels[receiver];
    if (currentModel == nullptr)
    {
        currentModel = chatModels[receiver] = new QStandardItemModel();
        currentModel->insertColumn(0);
    }

    int newRow = currentModel->rowCount();
    currentModel->insertRows(newRow, 2);
    currentModel->setData(currentModel->index(newRow, 0), ui->messageEdit->text());
    currentModel->setData(currentModel->index(newRow, 0), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);

    newRow++;
    QFont font;
    font.setPixelSize(8);
    currentModel->setData(currentModel->index(newRow, 0), QTime::currentTime().toString("hh:mm"));
    currentModel->setData(currentModel->index(newRow, 0), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);
    currentModel->setData(currentModel->index(newRow, 0), font, Qt::FontRole);
    //currentModel->setData(currentModel->index(newRow, 0), QBrush(Qt::white), Qt::ForegroundRole);

    ui->messageEdit->clear();
    ui->chatView->scrollToBottom();
}

void MainWindow::onMessageReceived(QString sender, QString text)
{
    QStandardItemModel *currentModel = chatModels[sender];
    if (currentModel == nullptr)
    {
        currentModel = chatModels[sender] = new QStandardItemModel();
        currentModel->insertColumn(0);
    }

    int newRow = currentModel->rowCount();
    currentModel->insertRows(newRow, 2);
    currentModel->setData(currentModel->index(newRow, 0), text);
    currentModel->setData(currentModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);

    newRow++;
    QFont font;
    font.setPixelSize(8);
    currentModel->setData(currentModel->index(newRow, 0), QTime::currentTime().toString("hh:mm"));
    currentModel->setData(currentModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
    currentModel->setData(currentModel->index(newRow, 0), font, Qt::FontRole);
}

void MainWindow::changeUser(QString currentUser)
{
    QStandardItemModel *currentModel = chatModels[currentUser];
    if (currentModel == nullptr)
    {
        currentModel = chatModels[currentUser] = new QStandardItemModel();
        currentModel->insertColumn(0);
    }

    ui->chatView->setModel(currentModel);
    ui->chatView->scrollToBottom();
}

void MainWindow::onDisconnectedFromServer()
{
    ui->sendButton->setEnabled(false);
    ui->messageEdit->setEnabled(false);
    ui->chatView->setEnabled(false);
    ui->loginButton->setEnabled(true);

    this->show();
    username = nullptr;

    QMessageBox::warning(this, "Disconnected", "The host terminated the connection");
}


void MainWindow::onUserJoined(QString username)
{
    ui->usersBox->addItem(username);
}

void MainWindow::onUserLeft(QString username)
{
    if (ui->usersBox->currentText() == username)
    {
        QMessageBox::warning(this, "Warning", "The user " + username + " left the chat.");
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

    ui->loginButton->setEnabled(true);
    ui->sendButton->setEnabled(false);
    ui->messageEdit->setEnabled(false);
    ui->chatView->setEnabled(false);
    this->show();

    username = nullptr;
}

