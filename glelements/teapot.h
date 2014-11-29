#ifndef TEAPOT_H
#define TEAPOT_H
#include "glelement.h"
class Teapot : public GLElement
{
private:
    static int counter;
public:
    Teapot();
//    void draw();
//    void draw_current();
    void just_draw_yourself(double size,bool isCurrent);
    ~Teapot();
};

#endif // TEAPOT_H
