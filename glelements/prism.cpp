#include "prism.h"

int Prism::counter = 0;
int Prism::index=0;
Prism::Prism()
{
    counter++;
    index++;
    type="prism";
    name=type+QString::number(index);
    delete list_ltem;
    list_ltem =new QListWidgetItem(name);
}

void Prism::just_draw_yourself(double size, bool isCurrent)
{
    SolidPrism(size);
    if(isCurrent)
    {
        glScalef(current_scale,current_scale,current_scale);
        WirePrism(size);
    }
}

void Prism::WirePrism(double size)
{
    double doublePI = PI * 2;
    double duration = doublePI / pointNum;
    double a, b;

    glBegin(GL_LINE_LOOP);
    glNormal3f(0, 0, -1.0);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        a = cos(angle);
        b = sin(angle);
        glVertex3f(a * size, b * size, 0);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glNormal3f(0, 0, 1.0);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        a = cos(angle);
        b = sin(angle);
        glVertex3f(a * size, b * size, 1);
    }
    glEnd();

    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        glBegin(GL_LINE_LOOP);
        // need a normal vector
        glVertex3f(cos(angle) * size, sin(angle) * size, 0);
        glVertex3f(cos(angle) * size, sin(angle) * size, 1);
        glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, 1);
        glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, 0);
        glEnd();
    }
}

void Prism::SolidPrism(double size)
{
    double doublePI = PI * 2;
    double duration = doublePI / pointNum;
    double a, b;

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, -1.0);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        a = cos(angle);
        b = sin(angle);
        glTexCoord2f(a / 2 + 0.5, b / 2 + 0.5); glVertex3f(a * size, b * size, 0);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1.0);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        a = cos(angle);
        b = sin(angle);
        glTexCoord2f(a / 2 + 0.5, b / 2 + 0.5); glVertex3f(a * size, b * size, 1);
    }
    glEnd();

    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        glBegin(GL_TRIANGLES);
        // need a normal vector
        glTexCoord2f(1, 0); glVertex3f(cos(angle) * size, sin(angle) * size, 0);
        glTexCoord2f(1, 1); glVertex3f(cos(angle) * size, sin(angle) * size, 1);
        glTexCoord2f(0, 1); glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, 1);

        glTexCoord2f(0, 0); glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, 0);
        glTexCoord2f(1, 0); glVertex3f(cos(angle) * size, sin(angle) * size, 0);
        glTexCoord2f(0, 1); glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, 1);
        glEnd();
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

Prism::~Prism()
{
    counter--;
}
