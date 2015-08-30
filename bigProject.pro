#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T15:20:01
#
#-------------------------------------------------

QT       += core gui\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bigProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    myresource.qrc

RC_FILE=images/logo.rc
