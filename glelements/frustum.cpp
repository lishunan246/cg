#include "frustum.h"

int Frustum::counter = 0;
int Frustum::index=0;
Frustum :: Frustum()
{
    counter++;
    index++;
    type = "frustum";
    name = type+QString::number(index);
    delete list_ltem;
    list_ltem = new QListWidgetItem(name);
}

void Frustum::just_draw_yourself(double size,bool isCurrent)
{
    frustum(size, false);
    if (isCurrent)
    {
        glScalef(current_scale,current_scale,current_scale);
        frustum(size, true);
    }
}

void Frustum::frustum(double size, bool isWire)		// XY平面为底 Z轴正向为高的正方向
{
    double doublePI = PI * 2;
    double duration = doublePI / pointNum;
    int mode = isWire ? GL_LINE_LOOP : GL_POLYGON;

    glBegin(mode);
    glNormal3f(0, 0, -1.0);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        glVertex3f(cos(angle) * size, sin(angle) * size, 0);
    }
    glEnd();

    glBegin(mode);
    glNormal3f(0, 0, 1.0);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        glVertex3f(cos(angle) * size * ratio, sin(angle) * size * ratio, 1);
    }
    glEnd();

    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        glBegin(mode);
        // need a normal vector
        glVertex3f(cos(angle) * size, sin(angle) * size, 0);
        glVertex3f(cos(angle) * size * ratio, sin(angle) * size * ratio, 1);
        glVertex3f(cos(angle + duration) * size  * ratio, sin(angle + duration) * size  * ratio, 1);
        glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, 0);
        glEnd();
    }
}

QDomElement Frustum::to_xml(QDomDocument *doc)
{
    QDomElement temp = GLElement::to_xml(doc);
    temp.setAttribute("pointNum",pointNum);
    temp.setAttribute("ratio",ratio);
    return temp;
}

void Frustum::from_xml(QDomElement dom)
{
    GLElement::from_xml(dom);
    XMLHelper::getAttribute(&dom,"pointNum",&pointNum);
    XMLHelper::getAttribute(&dom,"ratio",&ratio);
}

void Frustum::set_pointNum(int pointNum)
{
    this->pointNum = pointNum;
}

void Frustum::ser_ratio(double ratio)
{
    this->ratio = ratio;
}

Frustum::~Frustum()
{
    counter--;
}
