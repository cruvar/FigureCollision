#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T14:15:39
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FigureCollision
TEMPLATE = app


SOURCES += main.cpp\
    gamewindow.cpp

HEADERS  += \
    item.h \
    gamewindow.h \
    record.h

FORMS    += \
    gamewindow.ui

CONFIG += c++11

DISTFILES +=

RESOURCES += \
    recources.qrc
