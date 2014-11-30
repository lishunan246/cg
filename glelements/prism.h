#ifndef PRISM_H
#define PRISM_H
#include <GL/glut.h>
#include "glelement.h"

#define PI 3.1415926
class Prism : public GLElement
{
private:
    static int counter;
    int pointNum = 4;
public:
    Prism();
    void just_draw_yourself(double size,bool isCurrent);
    void prism(double size, bool isWire);
    void from_xml(QDomElement dom);
    QDomElement to_xml(QDomDocument* doc);
    void set_pointNum(int pointNum);
    ~Prism();
};

#endif // PRISM_H
