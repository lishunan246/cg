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
        double a, b;
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);
        glNormal3f(0, 0, 1);
        glVertex3f(0, 0, height);
        for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
            // need a normal vector
            a = cos(angle);
            b = sin(angle);
            glTexCoord2f(a / 2 + 0.5, b / 2 + 0.5); glVertex3f(a * radius, b * radius, 0);
        }
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0, 0, -1);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, 0, 0);
        for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
            a = cos(angle);
            b = sin(angle);
            glTexCoord2f(a / 2 + 0.5, b / 2 + 0.5); glVertex3f(a * radius, b * radius, 0);
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
        // need a normal vector
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
