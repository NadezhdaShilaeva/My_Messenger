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
    QHBoxLayout *horizontalLayout_4;
    QPushButton *loginButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_1;
    QPushButton *registerLabelButton;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *usernameEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *loginLabel;
    QHBoxLayout *horizontalLayout;
    QLineEdit *passwordEdit;
    QWidget *usersListPage;
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
    QWidget *registerPage;
    QGridLayout *gridLayout_5;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *registerLabel;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_2;
    QPushButton *loginLabelButton;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *registerButton;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *usernameRegEdit;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *passwordRegEdit;
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
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        loginButton = new QPushButton(loginPage);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setMinimumSize(QSize(150, 35));
        loginButton->setMaximumSize(QSize(150, 35));
        loginButton->setBaseSize(QSize(0, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(87);
        loginButton->setFont(font);
        loginButton->setCursor(QCursor(Qt::PointingHandCursor));
        loginButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgba(68, 123, 186, 1);\n"
"border-radius: 10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Calibri\";\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"background-color: rgba(68, 123, 186, 0.8);\n"
"}"));

        horizontalLayout_4->addWidget(loginButton);


        gridLayout_3->addLayout(horizontalLayout_4, 8, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_1 = new QLabel(loginPage);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 400 13pt \"Calibri\";"));
        label_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_1);

        registerLabelButton = new QPushButton(loginPage);
        registerLabelButton->setObjectName(QString::fromUtf8("registerLabelButton"));
        registerLabelButton->setCursor(QCursor(Qt::PointingHandCursor));
        registerLabelButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color:  transparent;\n"
"border: none;\n"
"color: rgb(0, 0, 0);\n"
"font: 700 13pt \"Calibri\";\n"
"text-align: left;\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"background-color:  transparent;\n"
"border: none;\n"
"color: rgb(0, 0, 0);\n"
"text-decoration: underline;\n"
"}"));

        horizontalLayout_5->addWidget(registerLabelButton);


        gridLayout_3->addLayout(horizontalLayout_5, 9, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 10, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        usernameEdit = new QLineEdit(loginPage);
        usernameEdit->setObjectName(QString::fromUtf8("usernameEdit"));
        usernameEdit->setMinimumSize(QSize(300, 35));
        usernameEdit->setMaximumSize(QSize(300, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Calibri"));
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        usernameEdit->setFont(font1);
        usernameEdit->setStyleSheet(QString::fromUtf8("QLineEdit\n"
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
        usernameEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(usernameEdit);


        gridLayout_3->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        loginLabel = new QLabel(loginPage);
        loginLabel->setObjectName(QString::fromUtf8("loginLabel"));
        loginLabel->setMinimumSize(QSize(0, 35));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Calibri"));
        font2.setPointSize(20);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(87);
        loginLabel->setFont(font2);
        loginLabel->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 700 20pt \"Calibri\";"));
        loginLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(loginLabel);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        passwordEdit = new QLineEdit(loginPage);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setMinimumSize(QSize(300, 35));
        passwordEdit->setMaximumSize(QSize(300, 16777215));
        passwordEdit->setStyleSheet(QString::fromUtf8("QLineEdit\n"
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
        passwordEdit->setEchoMode(QLineEdit::Password);
        passwordEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(passwordEdit);


        gridLayout_3->addLayout(horizontalLayout, 4, 0, 1, 1);

        stackedWidget->addWidget(loginPage);
        usersListPage = new QWidget();
        usersListPage->setObjectName(QString::fromUtf8("usersListPage"));
        usersListPage->setStyleSheet(QString::fromUtf8("background: transparent;"));
        gridLayout_4 = new QGridLayout(usersListPage);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        findUserEdit = new QLineEdit(usersListPage);
        findUserEdit->setObjectName(QString::fromUtf8("findUserEdit"));
        findUserEdit->setMinimumSize(QSize(300, 35));
        findUserEdit->setFont(font1);
        findUserEdit->setStyleSheet(QString::fromUtf8("QLineEdit\n"
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

        gridLayout_4->addWidget(findUserEdit, 0, 0, 1, 1);

        logoutButton2 = new QPushButton(usersListPage);
        logoutButton2->setObjectName(QString::fromUtf8("logoutButton2"));
        logoutButton2->setMinimumSize(QSize(100, 35));
        logoutButton2->setFont(font);
        logoutButton2->setCursor(QCursor(Qt::PointingHandCursor));
        logoutButton2->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgba(68, 123, 186, 1);\n"
"border-radius: 10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Calibri\";\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"background-color: rgba(68, 123, 186, 0.8);\n"
"}"));

        gridLayout_4->addWidget(logoutButton2, 0, 1, 1, 1);

        usersListView = new QListView(usersListPage);
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
"{\n"
"font: 400 14pt \"Calibri\";\n"
"border-bottom: 1px solid #dce1e6; \n"
"padding: 15px;\n"
"}\n"
"QListView::item:hover\n"
"{ \n"
"background-color:rgba(208, 219, 232, 100); \n"
"}\n"
"QListView::item:selected\n"
"{\n"
"color: rgb(0, 0, 0);\n"
"}\n"
""));
        usersListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        usersListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        usersListView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        usersListView->setIconSize(QSize(100, 32));

        gridLayout_4->addWidget(usersListView, 1, 0, 1, 2);

        stackedWidget->addWidget(usersListPage);
        chatPage = new QWidget();
        chatPage->setObjectName(QString::fromUtf8("chatPage"));
        chatPage->setStyleSheet(QString::fromUtf8("background: transparent;"));
        gridLayout_2 = new QGridLayout(chatPage);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        returnButton = new QPushButton(chatPage);
        returnButton->setObjectName(QString::fromUtf8("returnButton"));
        returnButton->setMinimumSize(QSize(100, 35));
        returnButton->setMaximumSize(QSize(100, 16777215));
        returnButton->setFont(font);
        returnButton->setCursor(QCursor(Qt::PointingHandCursor));
        returnButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgba(68, 123, 186, 1);\n"
"border-radius: 10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Calibri\";\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"background-color: rgba(68, 123, 186, 0.8);\n"
"}"));

        gridLayout_2->addWidget(returnButton, 0, 0, 1, 1);

        usernameLabel = new QLabel(chatPage);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Calibri"));
        font3.setPointSize(16);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        usernameLabel->setFont(font3);
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
        logoutButton->setFont(font);
        logoutButton->setCursor(QCursor(Qt::PointingHandCursor));
        logoutButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgba(68, 123, 186, 1);\n"
"border-radius: 10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Calibri\";\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"background-color: rgba(68, 123, 186, 0.8);\n"
"}"));

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
        messageEdit->setFont(font1);
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
        sendButton->setFont(font);
        sendButton->setCursor(QCursor(Qt::PointingHandCursor));
        sendButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgba(68, 123, 186, 1);\n"
"border-radius: 10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Calibri\";\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"background-color: rgba(68, 123, 186, 0.8);\n"
"}"));

        gridLayout_2->addWidget(sendButton, 2, 2, 1, 1);

        stackedWidget->addWidget(chatPage);
        registerPage = new QWidget();
        registerPage->setObjectName(QString::fromUtf8("registerPage"));
        gridLayout_5 = new QGridLayout(registerPage);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_3, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        registerLabel = new QLabel(registerPage);
        registerLabel->setObjectName(QString::fromUtf8("registerLabel"));
        registerLabel->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 700 20pt \"Calibri\";"));
        registerLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(registerLabel);


        gridLayout_5->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_2 = new QLabel(registerPage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 400 13pt \"Calibri\";"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_2);

        loginLabelButton = new QPushButton(registerPage);
        loginLabelButton->setObjectName(QString::fromUtf8("loginLabelButton"));
        loginLabelButton->setCursor(QCursor(Qt::PointingHandCursor));
        loginLabelButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color:  transparent;\n"
"border: none;\n"
"color: rgb(0, 0, 0);\n"
"font: 700 13pt \"Calibri\";\n"
"text-align: left;\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"background-color:  transparent;\n"
"border: none;\n"
"color: rgb(0, 0, 0);\n"
"text-decoration: underline;\n"
"}\n"
""));

        horizontalLayout_10->addWidget(loginLabelButton);


        gridLayout_5->addLayout(horizontalLayout_10, 5, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        registerButton = new QPushButton(registerPage);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));
        registerButton->setMinimumSize(QSize(150, 35));
        registerButton->setMaximumSize(QSize(150, 35));
        registerButton->setCursor(QCursor(Qt::PointingHandCursor));
        registerButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgba(68, 123, 186, 1);\n"
"border-radius: 10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Calibri\";\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"background-color: rgba(68, 123, 186, 0.8);\n"
"}"));

        horizontalLayout_9->addWidget(registerButton);


        gridLayout_5->addLayout(horizontalLayout_9, 4, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_4, 6, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        usernameRegEdit = new QLineEdit(registerPage);
        usernameRegEdit->setObjectName(QString::fromUtf8("usernameRegEdit"));
        usernameRegEdit->setMinimumSize(QSize(0, 35));
        usernameRegEdit->setMaximumSize(QSize(300, 16777215));
        usernameRegEdit->setStyleSheet(QString::fromUtf8("QLineEdit\n"
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
        usernameRegEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(usernameRegEdit);


        gridLayout_5->addLayout(horizontalLayout_7, 2, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        passwordRegEdit = new QLineEdit(registerPage);
        passwordRegEdit->setObjectName(QString::fromUtf8("passwordRegEdit"));
        passwordRegEdit->setMinimumSize(QSize(0, 35));
        passwordRegEdit->setMaximumSize(QSize(300, 16777215));
        passwordRegEdit->setStyleSheet(QString::fromUtf8("QLineEdit\n"
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
        passwordRegEdit->setEchoMode(QLineEdit::Password);
        passwordRegEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(passwordRegEdit);


        gridLayout_5->addLayout(horizontalLayout_8, 3, 0, 1, 1);

        stackedWidget->addWidget(registerPage);

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 550, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "My Messenger", nullptr));
        loginButton->setText(QApplication::translate("MainWindow", "Log in", nullptr));
        label_1->setText(QApplication::translate("MainWindow", "Don't have an account?", nullptr));
        registerLabelButton->setText(QApplication::translate("MainWindow", "Register", nullptr));
        usernameEdit->setPlaceholderText(QApplication::translate("MainWindow", "Username", nullptr));
        loginLabel->setText(QApplication::translate("MainWindow", "Login", nullptr));
        passwordEdit->setPlaceholderText(QApplication::translate("MainWindow", "Password", nullptr));
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
        registerLabel->setText(QApplication::translate("MainWindow", "Register", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Already have an account?", nullptr));
        loginLabelButton->setText(QApplication::translate("MainWindow", "Login", nullptr));
        registerButton->setText(QApplication::translate("MainWindow", "Register", nullptr));
        usernameRegEdit->setPlaceholderText(QApplication::translate("MainWindow", "Username", nullptr));
        passwordRegEdit->setPlaceholderText(QApplication::translate("MainWindow", "Password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
