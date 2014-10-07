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
    addnewprofiledialog.cpp

HEADERS  += mainwindow.h \
    database.h \
    profile.h \
    grade.h \
    addnewprofiledialog.h

FORMS    += mainwindow.ui \
    addnewprofiledialog.ui
CONFIG += c++11

