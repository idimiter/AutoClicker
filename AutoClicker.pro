#-------------------------------------------------
#
# Project created by QtCreator 2016-05-26T21:45:51
#
#-------------------------------------------------

QT += core gui widgets
LIBS += -luser32

CONFIG += c++11

include(QHotkey/qhotkey.pri)

TARGET = AutoClicker

TEMPLATE = app


SOURCES += main.cpp\
	ConfigWidget.cpp \
	MainWindow.cpp

HEADERS += MainWindow.h \
	ConfigWidget.h

RESOURCES += resources.qrc
