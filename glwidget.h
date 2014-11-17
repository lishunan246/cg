#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <GL/glut.h>
#include <QTimer>
#include <vector>
#include <GL/glu.h>
#include <QInputDialog>
#include <QImage>
#include <QDateTime>
#include <QFile>
#include <QtXml>
#include <QDomDocument>
#include <QMouseEvent>

#include "glelement.h"
#include "mainwindow.h"
#include "glelements.h"


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    QDomElement to_xml(QDomDocument* doc);
    void from_xml(QDomElement root);
public slots:
    void left();
    void up();
    void right();
    void down();
    void rotate_left();
    void rotate_right();
    void zoom_in();
    void zoom_out();
    void set_color();
    void set_position();
    void set_scale();
    void set_size();
    void set_current(QListWidgetItem* l);
    void screenshot();
    void add_element(GLElement* e);
    void add_teapot();
    void add_cube();
    void add_sphere();
    void delete_current();
    void delete_element(GLElement* e);
    void savetofile();
    void loadfile();
    //remove all GLElements
    void clear();

signals:
    void glelement_added(QListWidgetItem* l);
    void glelement_selected(QListWidgetItem* l);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w,int h);
    void mouseDoubleClickEvent(QMouseEvent *mouse);
protected:
    QTimer timer;
private:
    GLElement* currentElement=NULL;
    double eye[3];
    double thing[3];
    int rotate;
    std::vector<GLElement*> v;
    void initialize();
    void get_OGLPos(int x,int y);
};

#endif // GLWIDGET_H
