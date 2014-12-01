#include "cone.h"

int Cone::counter = 0;

Cone :: Cone()
{
    counter++;
    type = "cone";
    name = type+QString::number(counter);
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
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricTexture(obj, true);
    gluCylinder(obj, radius, 0, height, slice, 10);
//    double doublePI = PI * 2;
//    double duration = doublePI / slice;
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex3f(0, 0, height);
//    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
//        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0);
//    }
//    glEnd();

//    glBegin(GL_TRIANGLE_FAN);
//    glVertex3f(0, 0, 0);
//    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
//        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0);
//    }
//    glEnd();
}

void Cone::wireCone(double radius, double height, int slice)		// XY平面为底 Z轴正向为高的正方向
{
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_LINE);
    gluQuadricNormals(obj, GL_SMOOTH);
    gluCylinder(obj, radius, 0, height, slice, 10);
//    gluQuadricDrawStyle(obj, GLU_FILL);
//    double doublePI = PI * 2;
//    double duration = doublePI / slice;
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex3f(0, 0, height);
//    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
//        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0);
//    }
//    glEnd();

//    glBegin(GL_TRIANGLE_FAN);
//    glVertex3f(0, 0, 0);
//    for (double angle = 0; angle < doublePI + 0.1; angle += duration) {
//        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0);
//    }
//    glEnd();
}

Cone::~Cone()
{
    counter--;
}
