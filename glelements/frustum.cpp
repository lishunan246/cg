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
    SolidFrustum(size);
    if (isCurrent)
    {
        glScalef(current_scale,current_scale,current_scale);
        WireFrustum(size);
    }
}

void Frustum::WireFrustum(double size)
{
    double doublePI = PI * 2;
    double duration = doublePI / pointNum;
    double uppersize = size * ratio;
    double a, b;

    glBegin(GL_LINE_LOOP);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        a = cos(angle);
        b = sin(angle);
        glVertex3f(a * size, b * size, 0);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        a = cos(angle);
        b = sin(angle);
        glVertex3f(a * uppersize, b * uppersize, 1);
    }
    glEnd();

    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        glBegin(GL_LINE_LOOP);
        glVertex3f(cos(angle) * size, sin(angle) * size, 0);
        glVertex3f(cos(angle) * uppersize, sin(angle) * uppersize, 1);
        glVertex3f(cos(angle + duration) * uppersize, sin(angle + duration) * uppersize, 1);
        glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, 0);
        glEnd();
    }
}

void Frustum::SolidFrustum(double size)		// XY平面为底 Z轴正向为高的正方向
{
    double doublePI = PI * 2;
    double duration = doublePI / pointNum;
    double uppersize = size * ratio;
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
        glTexCoord2f(a / 2 + 0.5, b / 2 + 0.5); glVertex3f(a * uppersize, b * uppersize, 1);
    }
    glEnd();

    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        glBegin(GL_TRIANGLES);
        // need a normal vector			TO-DO
        // right up triangle
        glTexCoord2f(1, 0); glVertex3f(cos(angle) * size, sin(angle) * size, 0);
        glTexCoord2f(1, 1); glVertex3f(cos(angle) * uppersize, sin(angle) * uppersize, 1);
        glTexCoord2f(0, 1); glVertex3f(cos(angle + duration) * uppersize, sin(angle + duration) * uppersize, 1);
        // left down triangle
        glTexCoord2f(0, 0); glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, 0);
        glTexCoord2f(1, 0); glVertex3f(cos(angle) * size, sin(angle) * size, 0);
        glTexCoord2f(0, 1); glVertex3f(cos(angle + duration) * uppersize, sin(angle + duration) * uppersize, 1);
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
