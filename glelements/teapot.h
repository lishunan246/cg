#ifndef TEAPOT_H
#define TEAPOT_H
#include "glelement.h"
class Teapot : public GLElement
{
public:
    Teapot();
    void draw();
    void draw_current();
    void from_xml(QDomElement dom);

    ~Teapot();
};

#endif // TEAPOT_H
