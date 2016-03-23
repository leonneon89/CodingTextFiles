#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T16:44:45
#
#-------------------------------------------------

QT       += core gui

TARGET = CodingTextFiles
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        encodingFile.cpp

HEADERS  += mainwindow.h \
        encodingFile.h

FORMS    += mainwindow.ui

LIBS += -L/usr/local/lib/ -lenca
