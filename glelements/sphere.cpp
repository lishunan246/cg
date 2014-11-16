#include "sphere.h"

Sphere::Sphere()
{
    type="sphere";
    delete list_ltem;
    list_ltem =new QListWidgetItem(type);
}

void Sphere::draw()
{
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
       // glScalef(scaleX,scaleY,scaleZ);
        glScalef(scale[0],scale[1],scale[2]);
        glutSolidSphere(size,100,100);
        //glutSolidCube(1);

        glPopMatrix();
}

void Sphere::draw_current()
{
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
        glScalef(current_scale,current_scale,current_scale);
        glScalef(scale[0],scale[1],scale[2]);// glScalef(scaleX,scaleY,scaleZ);
        glutWireSphere(size,100,100);
        //glutSolidCube(1);

        glPopMatrix();
        draw();
}

Sphere::~Sphere()
{

}
