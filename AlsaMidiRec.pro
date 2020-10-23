#-------------------------------------------------
#
# Project created by QtCreator 2017-02-10T01:40:29
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlsaMidiRec
TEMPLATE = app




SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -lasound
