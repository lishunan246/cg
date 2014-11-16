#include "teapot.h"

Teapot::Teapot()
{
    type="teapot";
    delete list_ltem;
    list_ltem =new QListWidgetItem(type);
}

void Teapot::draw()
{
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
       // glScalef(scaleX,scaleY,scaleZ);
        glutSolidTeapot(size);
        //glutSolidCube(1);

        glPopMatrix();
}

void Teapot::draw_current()
{
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
        glScalef(current_scale,current_scale,current_scale);       // glScalef(scaleX,scaleY,scaleZ);
        glutWireTeapot(size);
        //glutSolidCube(1);

        glPopMatrix();
        draw();
}



Teapot::~Teapot()
{

}
