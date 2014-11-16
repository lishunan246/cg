#ifndef SPHERE_H
#define SPHERE_H
#include "glelement.h"
class Sphere : public GLElement
{
public:
    Sphere();
    void draw();
    void draw_current();
    ~Sphere();
};

#endif // SPHERE_H
