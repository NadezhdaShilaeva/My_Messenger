/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *usernameEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *loginButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QWidget *UsersListPage;
    QGridLayout *gridLayout_4;
    QLineEdit *findUserEdit;
    QPushButton *logoutButton2;
    QListView *usersListView;
    QWidget *chatPage;
    QGridLayout *gridLayout_2;
    QPushButton *returnButton;
    QLabel *usernameLabel;
    QPushButton *logoutButton;
    QListView *chatView;
    QLineEdit *messageEdit;
    QPushButton *sendButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(550, 630);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(208, 219, 232);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(208, 219, 232);"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setStyleSheet(QString::fromUtf8("background: transparent;"));
        loginPage = new QWidget();
        loginPage->setObjectName(QString::fromUtf8("loginPage"));
        loginPage->setStyleSheet(QString::fromUtf8("background: transparent;"));
        gridLayout_3 = new QGridLayout(loginPage);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        usernameEdit = new QLineEdit(loginPage);
        usernameEdit->setObjectName(QString::fromUtf8("usernameEdit"));
        usernameEdit->setMinimumSize(QSize(300, 35));
        usernameEdit->setMaximumSize(QSize(300, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        usernameEdit->setFont(font);
        usernameEdit->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"font: 400 14pt \"Calibri\";\n"
"border-radius: 10px;\n"
"border: 1px solid #dce1e6;\n"
"background: rgb(255, 255, 255);\n"
"}\n"
"QLineEdit:focus\n"
"{\n"
"border: 1px solid rgb(68, 123, 186);\n"
"}"));
        usernameEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(usernameEdit);


        gridLayout_3->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        loginButton = new QPushButton(loginPage);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setMinimumSize(QSize(150, 35));
        loginButton->setMaximumSize(QSize(150, 35));
        loginButton->setBaseSize(QSize(0, 0));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Calibri"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(87);
        loginButton->setFont(font1);
        loginButton->setCursor(QCursor(Qt::PointingHandCursor));
        loginButton->setStyleSheet(QString::fromUtf8("background-color: rgba(68, 123, 186, 1);\n"
"border-radius: 10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Calibri\";"));

        horizontalLayout_4->addWidget(loginButton);


        gridLayout_3->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(loginPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 35));
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 700 16pt \"Calibri\";"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 4, 0, 1, 1);

        stackedWidget->addWidget(loginPage);
        UsersListPage = new QWidget();
        UsersListPage->setObjectName(QString::fromUtf8("UsersListPage"));
        UsersListPage->setStyleSheet(QString::fromUtf8("background: transparent;"));
        gridLayout_4 = new QGridLayout(UsersListPage);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        findUserEdit = new QLineEdit(UsersListPage);
        findUserEdit->setObjectName(QString::fromUtf8("findUserEdit"));
        findUserEdit->setMinimumSize(QSize(300, 35));
        findUserEdit->setFont(font);
        findUserEdit->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"padding-left: 10px; \n"
"font: 400 14pt \"Calibri\";\n"
"border-radius: 10px;\n"
"border: 1px solid #dce1e6;\n"
"background: rgb(255, 255, 255);\n"
"}\n"
"QLineEdit:focus\n"
"{\n"
"border: 1px solid rgb(68, 123, 186);\n"
"}"));

        gridLayout_4->addWidget(findUserEdit, 0, 0, 1, 1);

        logoutButton2 = new QPushButton(UsersListPage);
        logoutButton2->setObjectName(QString::fromUtf8("logoutButton2"));
        logoutButton2->setMinimumSize(QSize(100, 35));
        logoutButton2->setFont(font1);
        logoutButton2->setCursor(QCursor(Qt::PointingHandCursor));
        logoutButton2->setStyleSheet(QString::fromUtf8("background-color: rgba(68, 123, 186, 1);\n"
"border-radius: 10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Calibri\";"));

        gridLayout_4->addWidget(logoutButton2, 0, 1, 1, 1);

        usersListView = new QListView(UsersListPage);
        usersListView->setObjectName(QString::fromUtf8("usersListView"));
        usersListView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        usersListView->setStyleSheet(QString::fromUtf8("QListView\n"
"{\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius: 10px;\n"
"border: 1px solid #dce1e6;\n"
"font: 400 14pt \"Calibri\";\n"
"outline: 0\n"
"}\n"
"QListView::item\n"
"{ \n"
"font: 400 14pt \"Calibri\";\n"
"border-bottom: 1px solid #dce1e6; \n"
"padding: 10px; \n"
"}\n"
"QListView::item:hover\n"
"{ \n"
"background-color:rgba(208, 219, 232, 100); \n"
"}"));
        usersListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        usersListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        usersListView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);

        gridLayout_4->addWidget(usersListView, 1, 0, 1, 2);

        stackedWidget->addWidget(UsersListPage);
        chatPage = new QWidget();
        chatPage->setObjectName(QString::fromUtf8("chatPage"));
        chatPage->setStyleSheet(QString::fromUtf8("background: transparent;"));
        gridLayout_2 = new QGridLayout(chatPage);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        returnButton = new QPushButton(chatPage);
        returnButton->setObjectName(QString::fromUtf8("returnButton"));
        returnButton->setMinimumSize(QSize(100, 35));
        returnButton->setMaximumSize(QSize(100, 16777215));
        returnButton->setFont(font1);
        returnButton->setCursor(QCursor(Qt::PointingHandCursor));
        returnButton->setStyleSheet(QString::fromUtf8("background-color: rgba(68, 123, 186, 1);\n"
"border-radius: 10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Calibri\";"));

        gridLayout_2->addWidget(returnButton, 0, 0, 1, 1);

        usernameLabel = new QLabel(chatPage);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Calibri"));
        font2.setPointSize(16);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        usernameLabel->setFont(font2);
        usernameLabel->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 400 16pt \"Calibri\";"));
        usernameLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(usernameLabel, 0, 1, 1, 1);

        logoutButton = new QPushButton(chatPage);
        logoutButton->setObjectName(QString::fromUtf8("logoutButton"));
        logoutButton->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(logoutButton->sizePolicy().hasHeightForWidth());
        logoutButton->setSizePolicy(sizePolicy1);
        logoutButton->setMinimumSize(QSize(100, 35));
        logoutButton->setFont(font1);
        logoutButton->setCursor(QCursor(Qt::PointingHandCursor));
        logoutButton->setStyleSheet(QString::fromUtf8("background-color: rgba(68, 123, 186, 1);\n"
"border-radius: 10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Calibri\";"));

        gridLayout_2->addWidget(logoutButton, 0, 2, 1, 1);

        chatView = new QListView(chatPage);
        chatView->setObjectName(QString::fromUtf8("chatView"));
        chatView->setStyleSheet(QString::fromUtf8("QListView\n"
"{\n"
"padding: 10px;\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius: 10px;\n"
"border: 1px solid #dce1e6;\n"
"outline: 0\n"
"}\n"
"QListView::item:hover\n"
"{ \n"
"color: rgb(0, 0, 0);\n"
"background-color: transparent;\n"
"}\n"
"QListView::item:selected\n"
"{ \n"
"color: rgb(0, 0, 0);\n"
"background-color: transparent;\n"
"}"));

        gridLayout_2->addWidget(chatView, 1, 0, 1, 3);

        messageEdit = new QLineEdit(chatPage);
        messageEdit->setObjectName(QString::fromUtf8("messageEdit"));
        messageEdit->setMinimumSize(QSize(200, 35));
        messageEdit->setFont(font);
        messageEdit->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"padding-left: 10px;\n"
"padding-right: 10px; \n"
"font: 400 14pt \"Calibri\";\n"
"border-radius: 10px;\n"
"border: 1px solid #dce1e6;\n"
"background: rgb(255, 255, 255);\n"
"}\n"
"QLineEdit:focus\n"
"{\n"
"border: 1px solid rgb(68, 123, 186);\n"
"}"));

        gridLayout_2->addWidget(messageEdit, 2, 0, 1, 2);

        sendButton = new QPushButton(chatPage);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(sendButton->sizePolicy().hasHeightForWidth());
        sendButton->setSizePolicy(sizePolicy2);
        sendButton->setMinimumSize(QSize(100, 35));
        sendButton->setMaximumSize(QSize(100, 16777215));
        sendButton->setFont(font1);
        sendButton->setCursor(QCursor(Qt::PointingHandCursor));
        sendButton->setStyleSheet(QString::fromUtf8("background-color: rgba(68, 123, 186, 1);\n"
"border-radius: 10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Calibri\";"));

        gridLayout_2->addWidget(sendButton, 2, 2, 1, 1);

        stackedWidget->addWidget(chatPage);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 550, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "My Messenger", nullptr));
        usernameEdit->setPlaceholderText(QApplication::translate("MainWindow", "Username", nullptr));
        loginButton->setText(QApplication::translate("MainWindow", "Log in", nullptr));
        label->setText(QApplication::translate("MainWindow", "Enter your username:", nullptr));
        findUserEdit->setPlaceholderText(QApplication::translate("MainWindow", "Find a user...", nullptr));
        logoutButton2->setText(QApplication::translate("MainWindow", "Log out", nullptr));
        returnButton->setText(QApplication::translate("MainWindow", "\342\200\271 Back", nullptr));
#ifndef QT_NO_WHATSTHIS
        usernameLabel->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        usernameLabel->setText(QApplication::translate("MainWindow", "Username", nullptr));
        logoutButton->setText(QApplication::translate("MainWindow", "Log out", nullptr));
        messageEdit->setPlaceholderText(QApplication::translate("MainWindow", "Write a message...", nullptr));
        sendButton->setText(QApplication::translate("MainWindow", "Send \342\200\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
