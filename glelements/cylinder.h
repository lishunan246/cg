#ifndef CYLINDER_H
#define CYLINDER_H
#include <GL/glut.h>
#include "glelement.h"

#define PI 3.1415926
class Cylinder : public GLElement
{
private:
    static int counter;
    static int index;
public:
    Cylinder();
    void just_draw_yourself(double size,bool isCurrent);
    void solidCylinder(double radius, double height, int slice = 36);
    void wireCylinder(double radius, double height, int slice = 36);
    ~Cylinder();
};
#endif // CYLINDER_H
