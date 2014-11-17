#include "teapot.h"

int Teapot::counter=0;
Teapot::Teapot()
{
    counter++;
    type="teapot";
    name=type+QString::number(counter);
    delete list_ltem;
    list_ltem =new QListWidgetItem(name);
}

void Teapot::draw()
{
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
       // glScalef(scaleX,scaleY,scaleZ);
        glScalef(scale[0],scale[1],scale[2]);
        glutSolidTeapot(size);
        //glutSolidCube(1);

        glPopMatrix();
}

void Teapot::draw_current()
{
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
        glScalef(current_scale,current_scale,current_scale);
        glScalef(scale[0],scale[1],scale[2]);// glScalef(scaleX,scaleY,scaleZ);
        glutWireTeapot(size);
        //glutSolidCube(1);

        glPopMatrix();
        draw();
}



Teapot::~Teapot()
{
    counter--;
}
