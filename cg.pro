#-------------------------------------------------
#
# Project created by QtCreator 2014-11-04T07:34:38
#
#-------------------------------------------------

QT       += core gui opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cg
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    glelement.cpp \
    glelements/cube.cpp \
    glelements/teapot.cpp \
    glelements/sphere.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    glelement.h \
    glelements/cube.h \
    glelements.h \
    glelements/teapot.h \
    glelements/sphere.h

FORMS    += mainwindow.ui

LIBS +=-lglut -lGLU
