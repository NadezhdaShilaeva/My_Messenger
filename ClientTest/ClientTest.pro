QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../Client

SOURCES +=  \
    ChatServiceTest.cpp \
    ../Client/ChatService.cpp

HEADERS += \
    ChatServiceTest.h \
    ../Client/ChatService.h
