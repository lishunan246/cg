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
    glRotated(270,1,0,0);
    SolidPrism(size);
    if(isCurrent)
    {
        glScalef(current_scale,current_scale,current_scale);
        WirePrism(size);
    }
}

void Prism::WirePrism(double size)
{
    double height = 1;
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
        glVertex3f(a * size, b * size, height);
    }
    glEnd();

    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        glBegin(GL_LINE_LOOP);
        glVertex3f(cos(angle) * size, sin(angle) * size, 0);
        glVertex3f(cos(angle) * size, sin(angle) * size, height);
        glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, height);
        glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, 0);
        glEnd();
    }
}

void Prism::SolidPrism(double size)
{
    double height = 1;
    double doublePI = PI * 2;
    double duration = doublePI / pointNum;
    double xCurrent, yCurrent, xNext, yNext;

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, -1.0);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        xCurrent = cos(angle);
        yCurrent = sin(angle);
        glTexCoord2f(xCurrent / 2 + 0.5, yCurrent / 2 + 0.5); glVertex3f(xCurrent * size, yCurrent * size, 0);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1.0);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        xCurrent = cos(angle);
        yCurrent = sin(angle);
        glTexCoord2f(xCurrent / 2 + 0.5, yCurrent / 2 + 0.5); glVertex3f(xCurrent * size, yCurrent * size, height);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        xCurrent = cos(angle);
        yCurrent = sin(angle);
        xNext = cos(angle + duration);
        yNext = sin(angle + duration);

        GLfloat * normalVector = new GLfloat[3];
        float a[3] = {xNext - xCurrent, yNext - yCurrent, 0};
        float b[3] = {0, 0, -height};
        cal_normal_vector(normalVector, b, a);
        glNormal3fv(normalVector);

        // right up triangle
        glTexCoord2f(1, 0); glVertex3f(xCurrent * size, yCurrent * size, 0);
        glTexCoord2f(1, 1); glVertex3f(xCurrent * size, yCurrent * size, height);
        glTexCoord2f(0, 1); glVertex3f(xNext * size, yNext * size, height);
        // left down triangle
        glTexCoord2f(0, 0); glVertex3f(xNext * size, yNext * size, 0);
        glTexCoord2f(1, 0); glVertex3f(xCurrent * size, yCurrent * size, 0);
        glTexCoord2f(0, 1); glVertex3f(xNext * size, yNext * size, height);
        delete [] normalVector;
    }
    glEnd();
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
