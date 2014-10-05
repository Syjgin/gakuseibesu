#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T20:22:06
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gakuseibesu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        database.cpp \

HEADERS  += mainwindow.h \
    database.h \
    profile.h \
    grade.h \

FORMS    += mainwindow.ui
CONFIG += c++11

