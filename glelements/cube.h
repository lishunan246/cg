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
    ~Cube();
};

#endif // CUBE_H