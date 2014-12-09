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
#include "objhandler.h"
#include "ui/colordialog.h"
#include "ui/lightdialog.h"
#include "light.h"
#include "xmlhelper.h"
#include "vertice.h"
#include "mtllib.h"
#include "loadobj.h"
#include "texturemanager.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    QDomElement to_xml(QDomDocument* doc);
    void from_xml(QDomElement root);
public slots:
    void config_light();

    void left();
    void up();
    void right();
    void down();
    void rotate_left();
    void rotate_right();
    void zoom_in();
    void zoom_out();
    void load_obj();
    void rename();
    void set_color();
    void set_point_number();
    void set_position();
    void set_scale();
    void set_shininess();
    void set_size();
    void set_texture();
    void clear_texture();
    void set_rotate_angle();
    void set_rotate_speed();
    void set_current(QListWidgetItem* l);
    void screenshot();
    void add_element(GLElement* e);
    void add_teapot();
    void add_cube();
    void add_cylinder();
    void add_sphere();
    void add_cone();
    void add_prism();
    void add_frustum();
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
    void mousePressEvent(QMouseEvent *mouse);
    void mouseReleaseEvent(QMouseEvent *mouse);
    void mouseMoveEvent(QMouseEvent *mouse);
protected:
    QTimer timer;
private:
    GLElement* currentElement=NULL;
    double eye[3];
    double thing[3];
    int rotate;

    bool rotateMode=false;
    int lastXPos,lastYPos;

    std::vector<GLElement*> v;
    Light* l[8];
    void get_OGLPos(int x,int y);
};

#endif // GLWIDGET_H
