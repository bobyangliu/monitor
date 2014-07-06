#-------------------------------------------------
#
# Project created by QtCreator 2014-04-22T09:20:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app

INCLUDEPATH += /usr/local/include
LIBS += -pthread -L/usr/local/lib -lavdevice -lavfilter -lpostproc -lswresample -lswscale -lavformat -lavcodec -ldl -lX11 -lx264 -lz -lavutil -lm

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

OTHER_FILES +=



