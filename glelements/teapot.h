#ifndef TEAPOT_H
#define TEAPOT_H
#include "glelement.h"
class teapot : public GLElement
{
public:
    teapot();
    void draw();
    void draw_current();
    void from_xml(QDomElement dom);

    ~teapot();
};

#endif // TEAPOT_H
