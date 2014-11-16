#ifndef CUBE_H
#define CUBE_H
#include <GL/glut.h>
#include "glelement.h"

class Cube : public GLElement
{
public:
    Cube();
    void draw();
    void draw_current();
    void from_xml(QDomElement dom);
    ~Cube();
};

#endif // CUBE_H
