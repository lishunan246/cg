#include "sphere.h"
int Sphere::counter=0;
Sphere::Sphere()
{
    counter++;
    type="sphere";
    name=type+QString::number(counter);
    delete list_ltem;
    list_ltem =new QListWidgetItem(name);
}

void Sphere::just_draw_yourself(double size, bool isCurrent)
{
    glutSolidSphere(size,100,100);
    if(isCurrent)
    {
        glScalef(current_scale,current_scale,current_scale);
        glutWireSphere(size,100,100);
    }
}

//void Sphere::draw()
//{
//    glPushMatrix();
//        glTranslatef(position[0],position[1],position[2]);
//        set_glMaterial();
//       // glScalef(scaleX,scaleY,scaleZ);
//        glScalef(scale[0],scale[1],scale[2]);
//        glutSolidSphere(size,100,100);
//        //glutSolidCube(1);

//        glPopMatrix();
//}

//void Sphere::draw_current()
//{
//    glPushMatrix();
//        glTranslatef(position[0],position[1],position[2]);
//        set_glMaterial();
//        glScalef(current_scale,current_scale,current_scale);
//        glScalef(scale[0],scale[1],scale[2]);// glScalef(scaleX,scaleY,scaleZ);
//        glutWireSphere(size,100,100);
//        //glutSolidCube(1);

//        glPopMatrix();
//        draw();
//}

Sphere::~Sphere()
{
    counter--;
}
