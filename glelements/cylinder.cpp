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
    solidCylinder(size, size);
    if (isCurrent)
    {
        glScalef(current_scale,current_scale,current_scale);
        wireCylinder(size, size);
    }
}

void Cylinder::solidCylinder(double radius, double height, int slice)		// XY平面为底 Z轴正向为高的正方向
{
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricTexture(obj, true);
    gluCylinder(obj, radius, radius, height, slice, 10);
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
