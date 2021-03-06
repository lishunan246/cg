#ifndef FRUSTUM_H
#define FRUSTUM_H
#include <GL/glut.h>
#include "glelement.h"

#define PI 3.1415926
class Frustum : public GLElement
{
private:
    static int counter;
    static int index;
    int pointNum = 4;
    double ratio = 0.5;
public:
    Frustum();
    void just_draw_yourself(double size,bool isCurrent);
    void SolidFrustum(double size);
    void WireFrustum(double size);
    QDomElement to_xml(QDomDocument* doc);
    void from_xml(QDomElement dom);
    void set_pointNum(int pointNum);
    void ser_ratio(double ratio);
    ~Frustum();
};

#endif // FRUSTUM_H
