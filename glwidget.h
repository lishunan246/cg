#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "glelement.h"
#include <GL/glut.h>
#include <QTimer>
#include <vector>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
public slots:
    void left();
    void up();
    void right();
    void down();
    void zoom_in();
    void zoom_out();
    void set_color();
    void set_position();
    void set_size();
    void screenshot();
    void add_teapot();
    void clear();

signals:
    void glelement_added();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w,int h);
protected:
    QTimer timer;
private:
    GLElement* currentElement=NULL;
    double eye[3];
    double thing[3];
    int rotate;
    std::vector<GLElement*> v;
};

#endif // GLWIDGET_H
