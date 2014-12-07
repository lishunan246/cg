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
    double height = 1;
    double doublePI = PI * 2;
    double duration = doublePI / pointNum;
    double uppersize = size * ratio;
    double xCurrent, yCurrent;

    glBegin(GL_LINE_LOOP);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        xCurrent = cos(angle);
        yCurrent = sin(angle);
        glVertex3f(xCurrent * size, yCurrent * size, 0);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        xCurrent = cos(angle);
        yCurrent = sin(angle);
        glVertex3f(xCurrent * uppersize, yCurrent * uppersize, height);
    }
    glEnd();

    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        glBegin(GL_LINE_LOOP);
        glVertex3f(cos(angle) * size, sin(angle) * size, 0);
        glVertex3f(cos(angle) * uppersize, sin(angle) * uppersize, height);
        glVertex3f(cos(angle + duration) * uppersize, sin(angle + duration) * uppersize, height);
        glVertex3f(cos(angle + duration) * size, sin(angle + duration) * size, 0);
        glEnd();
    }
}

void Frustum::SolidFrustum(double size)		// XY平面为底 Z轴正向为高的正方向
{
    double doublePI = PI * 2;
    double height = 1;
    double duration = doublePI / pointNum;
    double uppersize = size * ratio;
    double xCurrent, yCurrent, xNext, yNext;

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, -1.0);
    for (double angle = 0; abs(angle - doublePI) > 0.01; angle += duration) {
        xCurrent = cos(angle);
        yCurrent = sin(angle);
        glTexCoord2f(xCurrent / 2 + 0.5, yCurrent / 2 + 0.5); glVertex3f(xCurrent * size, yCurrent * size, 0);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1.0);
    for (double angle = 0; abs(angle - doublePI) > 0.01; angle += duration) {
        xCurrent = cos(angle);
        yCurrent = sin(angle);
        glTexCoord2f(xCurrent / 2 + 0.5, yCurrent / 2 + 0.5); glVertex3f(xCurrent * uppersize, yCurrent * uppersize, height);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    for (double angle = 0; abs(angle - doublePI) > 0.01; angle += duration) {
        xCurrent = cos(angle);
        yCurrent = sin(angle);
        xNext = cos(angle + duration);
        yNext = sin(angle + duration);

        GLfloat * normalVector = new GLfloat[3];
        float a[3] = {xNext - xCurrent, yNext - yCurrent, 0};
        float b[3] = {xCurrent * size - xCurrent * uppersize, yCurrent * size - yCurrent * uppersize, -height};
        cal_normal_vector(normalVector, b, a);
        glNormal3fv(normalVector);

        // right up triangle
        glTexCoord2f(1, 0); glVertex3f(xCurrent * size, yCurrent * size, 0);
        glTexCoord2f(1, 1); glVertex3f(xCurrent * uppersize, yCurrent * uppersize, height);
        glTexCoord2f(0, 1); glVertex3f(xNext * uppersize, yNext * uppersize, height);
        // left down triangle
        glTexCoord2f(0, 0); glVertex3f(xNext * size, yNext * size, 0);
        glTexCoord2f(1, 0); glVertex3f(xCurrent * size, yCurrent * size, 0);
        glTexCoord2f(0, 1); glVertex3f(xNext * uppersize, yNext * uppersize, height);
        delete [] normalVector;
    }
    glEnd();
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
