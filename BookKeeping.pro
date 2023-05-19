# -------------------------------------------------
# Project created by QtCreator 2010-06-24T22:51:49
# -------------------------------------------------
QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BoookKeeping
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    viewgjentry.cpp \
    viewglaccount.cpp \
    viewgj.cpp

HEADERS += mainwindow.h \
    viewgjentry.h \
    viewglaccount.h \
    viewgj.h

FORMS += mainwindow.ui \
    viewGJentry.ui \
    viewGLaccount.ui \
    viewGJ.ui
