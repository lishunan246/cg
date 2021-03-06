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
    ui/colordialog.cpp \
    light.cpp \
    xmlhelper.cpp \
    ui/lightdialog.cpp \
    glelements/cone.cpp \
    glelements/cylinder.cpp \
    glelements/prism.cpp \
    glelements/frustum.cpp \
    loadobj.cpp \
    mtllib.cpp \
    texturemanager.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    glelement.h \
    glelements/cube.h \
    glelements.h \
    glelements/teapot.h \
    glelements/sphere.h \
    ui/colordialog.h \
    light.h \
    xmlhelper.h \
    ui/lightdialog.h \
    glelements/cone.h \
    glelements/cylinder.h \
    glelements/prism.h \
    glelements/frustum.h \
    loadobj.h \
    mtllib.h \
    vertice.h \
    texturemanager.h

FORMS    += mainwindow.ui \
    ui/colordialog.ui \
    ui/lightdialog.ui

LIBS +=-lglut -lGLU

QMAKE_CXXFLAGS += -std=c++11
