#include "prism.h"

int Prism::counter = 0;

Prism::Prism()
{
    counter++;
    type="prism";
    name=type+QString::number(counter);
    delete list_ltem;
    list_ltem =new QListWidgetItem(name);
}

void Prism::just_draw_yourself(double size, bool isCurrent)
{
    prism(size, false);
    if(isCurrent)
    {
        glScalef(current_scale,current_scale,current_scale);
        prism(size, true);
    }
}

void Prism::from_xml(QDomElement dom)
{
    GLElement::from_xml(dom);
    XMLHelper::getAttribute(&dom,"pointNum",&pointNum);
}

QDomElement Prism::to_xml(QDomDocument *doc)
{
    QDomElement temp = GLElement::to_xml(doc);
    temp.setAttribute("pointNum",pointNum);
    return temp;
}

void Prism::set_pointNum(int pointNum)
{
    this->pointNum = pointNum;
}

void Prism::prism(double size, bool isWire)
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
        glVertex3f(cos(angle) * size, sin(angle) * size, 1);
    }
    glEnd();

    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        glBegin(mode);
        //need a normal vector
        glVertex3f(cos(angle) * size, sin(angle) * size, 0);
        glVertex3f(cos(angle) * size, sin(angle) * size, 1);
        glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, 1);
        glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, 0);
        glEnd();
    }
}

Prism::~Prism()
{
    counter--;
}
