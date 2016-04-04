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
        dialog.cpp \
    item.cpp

HEADERS  += dialog.h \
    item.h

FORMS    += dialog.ui

CONFIG += c++11
