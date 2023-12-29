QT += testlib network widgets
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../Client

SOURCES +=  \
    ../Client/ChatService.cpp \
    ChatServiceTest.cpp \
    ../Client/LoginService.cpp \
    LoginServiceTest.cpp \
    SessionMock.cpp \
    main.cpp

HEADERS += \
    ../Client/ChatService.h \
    ChatServiceTest.h \
    ../Client/LoginService.h \
    LoginServiceTest.h \
    ../Client/ISession.h \
    SessionMock.h
