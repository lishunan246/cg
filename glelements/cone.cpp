#include "cone.h"

int Cone::counter = 0;
int Cone::index=0;

Cone :: Cone()
{
    counter++;
    index++;
    type = "cone";
    name = type+QString::number(index);
    delete list_ltem;
    list_ltem = new QListWidgetItem(name);
}

void Cone::just_draw_yourself(double size,bool isCurrent)
{
    glRotated(270,1,0,0);
    solidCone(size, size);
    if (isCurrent)
    {
        glScalef(current_scale,current_scale,current_scale);
        wireCone(size, size);
    }
}

void Cone::solidCone(double radius, double height, int slice)		// XY平面为底 Z轴正向为高的正方向
{
        double doublePI = PI * 2;
        double duration = doublePI / slice;
        double xCurrent, yCurrent, xNext, yNext;
        glBegin(GL_TRIANGLES);
        for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
            xCurrent = cos(angle);
            yCurrent = sin(angle);
            xNext = cos(angle + duration);
            yNext = sin(angle + duration);

            GLfloat * normalVector = new GLfloat[3];
            float a[3] = {xCurrent * radius, yCurrent * radius, -height};
            float b[3] = {xNext * radius, yNext * radius, -height};
            cal_normal_vector(normalVector, a, b);
            glNormal3fv(normalVector);

            glTexCoord2f((angle / doublePI), 1); glVertex3f(0, 0, height);
            glTexCoord2f((angle / doublePI), 0); glVertex3f(xCurrent * radius, yCurrent * radius, 0);
            glTexCoord2f(((angle + duration) / doublePI), 0); glVertex3f(xNext * radius, yNext * radius, 0);
            delete [] normalVector;
        }
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0, 0, -1);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, 0, 0);
        for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
            xCurrent = cos(angle);
            yCurrent = sin(angle);
            glTexCoord2f(xCurrent / 2 + 0.5, yCurrent / 2 + 0.5); glVertex3f(xCurrent * radius, yCurrent * radius, 0);
        }
        glEnd();
}

void Cone::wireCone(double radius, double height, int slice)		// XY平面为底 Z轴正向为高的正方向
{
    double doublePI = PI * 2;
    double duration = doublePI / slice;
    double a, b;
    glBegin(GL_LINE_LOOP);
    glNormal3f(0, 0, 0);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        glVertex3f(0, 0, height);
        a = cos(angle);
        b = sin(angle);
        glVertex3f(a * radius, b * radius, 0);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glNormal3f(0, 0, 0);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        a = cos(angle);
        b = sin(angle);
        glVertex3f(a * radius, b * radius, 0);
    }
    glEnd();
}

Cone::~Cone()
{
    counter--;
}
