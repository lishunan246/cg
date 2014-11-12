#ifndef GLELEMENT_H
#define GLELEMENT_H
#include <QGLWidget>
#include <GL/glut.h>

class GLElement
{
private:
    void* parent;//it is acutually GLWidget*
    GLfloat color[4];
    GLfloat position[3];
    GLdouble size;
public:
    GLElement(void* parent);
    void draw();
    void set_color(GLfloat* color4);
    void set_position(GLfloat* position3);
    void set_size(GLdouble s);
};

#endif // GLELEMENT_H
