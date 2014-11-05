#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include <GL/glut.h>
#include <QTimer>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w,int h);
protected:
    QTimer timer;

};

#endif // GLWIDGET_H
