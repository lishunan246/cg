#ifndef GLELEMENT_H
#define GLELEMENT_H
#include <QGLWidget>
#include <GL/glut.h>

class GLElement
{
private:
    GLfloat color[4];
    GLfloat position[3];
public:
    GLElement();
    void draw();
    void set_color(GLfloat* color4);
    void set_position(GLfloat* position3);
};

#endif // GLELEMENT_H
