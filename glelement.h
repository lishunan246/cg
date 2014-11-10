#ifndef GLELEMENT_H
#define GLELEMENT_H
#include <QGLWidget>
#include <GL/glut.h>

class GLElement
{
private:
    GLfloat color[4];
public:
    GLElement();
    void draw();
    void set_color(GLfloat* color3);
};

#endif // GLELEMENT_H
