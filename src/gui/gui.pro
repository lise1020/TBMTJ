#-------------------------------------------------
#
# Project created by QtCreator 2015-08-31T11:29:33
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app
DESTDIR = ../../../bin


RESOURCES = ../../res/res.qrc

include ( /opt/PythonQt3.0/build/PythonQt.prf )


SOURCES += main.cpp\
           mainwindow.cpp \
           tbproject.cpp \
           spec.cpp
           PythonQtScriptingConsole.cpp

HEADERS += mainwindow.h \
           tbproject.h \
           spec.h
           PythonQtScriptingConsole.h

FORMS   += mainwindow.ui


