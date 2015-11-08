#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T11:39:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


LIBS += -lglut


SOURCES += main.cpp\
        mainwindow.cpp \
    portalwindow.cpp \
    tbproject.cpp \
    schema3layer.cpp

HEADERS  += mainwindow.h \
    portalwindow.h \
    tbproject.h \
    schema3layer.h

FORMS    += mainwindow.ui \
    portalwindow.ui \
    tbproject.ui
