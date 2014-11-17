#ifndef TEAPOT_H
#define TEAPOT_H
#include "glelement.h"
class Teapot : public GLElement
{
private:
    static int counter;
public:
    Teapot();
    void draw();
    void draw_current();
    ~Teapot();
};

#endif // TEAPOT_H
