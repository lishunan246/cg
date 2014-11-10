#-------------------------------------------------
#
# Project created by QtCreator 2014-11-04T07:34:38
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cg
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    glelement.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    glelement.h

FORMS    += mainwindow.ui

LIBS +=-lglut -lGLU
