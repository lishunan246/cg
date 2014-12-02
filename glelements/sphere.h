#ifndef SPHERE_H
#define SPHERE_H
#include "glelement.h"
class Sphere : public GLElement
{
private:
    static int counter;
    static int index;
public:
    Sphere();
//    void draw();
//    void draw_current();
    void just_draw_yourself(double size,bool isCurrent);
    ~Sphere();
};

#endif // SPHERE_H
