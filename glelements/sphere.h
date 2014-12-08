#ifndef SPHERE_H
#define SPHERE_H
#include "glelement.h"

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Point;

class Sphere : public GLElement
{
private:
    static int counter;
    static int index;
public:
    Sphere();
    void just_draw_yourself(double size,bool isCurrent);
    void solidSphere(double radius, int slices, int stacks);
    void wireSphere(double radius, int slices, int stacks);
    GLfloat * mean3(const GLfloat a[3], const GLfloat b[3], const GLfloat c[3]);
    ~Sphere();
};

#endif // SPHERE_H
