#ifndef CUBE_H
#define CUBE_H
#include <GL/glut.h>
#include "glelement.h"

class Cube : public GLElement
{
private:
    static int counter;
    static int index;
public:
    Cube();
//    void draw();
//    void draw_current();
    void just_draw_yourself(double size,bool isCurrent);
    void solidCube(double size);
    ~Cube();
};

#endif // CUBE_H
