#include "cylinder.h"

int Cylinder::counter = 0;
int Cylinder::index=0;
Cylinder :: Cylinder()
{
    counter++;
    index++;
    type = "cylinder";
    name = type+QString::number(index);
    delete list_ltem;
    list_ltem = new QListWidgetItem(name);
}

void Cylinder::just_draw_yourself(double size,bool isCurrent)
{
    glRotated(270,1,0,0);
    solidCylinder(size, size);
    if (isCurrent)
    {
        glScalef(current_scale,current_scale,current_scale);
        wireCylinder(size, size);
    }
}

void Cylinder::solidCylinder(double radius, double height, int slice)		// XY平面为底 Z轴正向为高的正方向
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

        glNormal3f(cos(angle + duration / 2), sin(angle + duration / 2), 0);
        glTexCoord2f(0, radius * angle / height); glVertex3f(xCurrent * radius, yCurrent * radius, 0);
        glTexCoord2f(0, radius * (angle + duration) / height); glVertex3f(xNext * radius, yNext * radius, 0);
        glTexCoord2f(1, radius * angle / height); glVertex3f(xCurrent * radius, yCurrent * radius, height);

        glTexCoord2f(1, radius * (angle + duration) / height); glVertex3f(xNext * radius, yNext * radius, height);
        glTexCoord2f(1, radius * angle / height); glVertex3f(xCurrent * radius, yCurrent * radius, height);
        glTexCoord2f(0, radius * (angle + duration) / height); glVertex3f(xNext * radius, yNext * radius, 0);
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

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, 0, height);
    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
        xCurrent = cos(angle);
        yCurrent = sin(angle);
        glTexCoord2f(xCurrent / 2 + 0.5, yCurrent / 2 + 0.5); glVertex3f(xCurrent * radius, yCurrent * radius, height);
    }
    glEnd();
}

void Cylinder::wireCylinder(double radius, double height, int slice)		// XY平面为底 Z轴正向为高的正方向
{
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_LINE);
    gluQuadricNormals(obj, GL_SMOOTH);
//        gluQuadricDrawStyle(obj, GLU_FILL);
    gluCylinder(obj, radius, radius, height, slice, 10);
}

Cylinder::~Cylinder()
{
    counter--;
}
