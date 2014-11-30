#ifndef CONE_H
#define CONE_H
#include <GL/glut.h>
#include "glelement.h"

#define PI 3.1415926
class Cone : public GLElement
{
private:
    static int counter;
public:
    Cone();
    void just_draw_yourself(double size,bool isCurrent);
    void solidCone(double radius, double height, int slice = 36);
    void wireCone(double radius, double height, int slice = 36);
    ~Cone();
};

#endif // CONE_H
