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
public slots:
    void left();
    void up();
    void right();
    void down();
    void zoom_in();
    void zoom_out();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w,int h);
protected:
    QTimer timer;
private:
    double eye[3];
    double thing[3];
    int rotate;
};

#endif // GLWIDGET_H
