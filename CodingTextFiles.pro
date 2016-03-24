#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T16:44:45
#
#-------------------------------------------------

QT       += core gui

TARGET = CodingTextFiles
TEMPLATE = app

INCLUDEPATH +=$$PWD/include/
INCLUDEPATH +=$$PWD/

SOURCES += $$PWD/main.cpp\
        $$PWD/mainwindow.cpp \
        $$PWD/encodingFile.cpp \
        $$PWD/directoryWork.cpp

HEADERS  += $$PWD/mainwindow.h \
        $$PWD/encodingFile.h \
        $$PWD/directoryWork.h

FORMS    += $$PWD/mainwindow.ui

#LIBS += -L/usr/local/lib/ -lenca
LIBS += -L/$$PWD/lib/ -lenca
