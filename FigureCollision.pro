#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T14:15:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FigureCollision
TEMPLATE = app


SOURCES += main.cpp\
    gamewindow.cpp \
    recordswindow.cpp

HEADERS  += \
    item.h \
    gamewindow.h \
    recordswindow.h \
    record.h

FORMS    += \
    gamewindow.ui \
    recordswindow.ui

CONFIG += c++11

DISTFILES +=

RESOURCES += \
    fonts.qrc
