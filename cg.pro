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
    glelements/sphere.cpp \
    objhandler.cpp \
    ui/colordialog.cpp \
    light.cpp \
    xmlhelper.cpp \
    glelements/cone.cpp \
    glelements/cylinder.cpp \
    glelements/prism.cpp \
    glelements/frustum.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    glelement.h \
    glelements/cube.h \
    glelements.h \
    glelements/teapot.h \
    glelements/sphere.h \
    objhandler.h \
    ui/colordialog.h \
    light.h \
    xmlhelper.h \
    glelements/cone.h \
    glelements/cylinder.h \
    glelements/prism.h \
    glelements/frustum.h

FORMS    += mainwindow.ui \
    ui/colordialog.ui

LIBS +=-lglut -lGLU

QMAKE_CXXFLAGS += -std=c++11
