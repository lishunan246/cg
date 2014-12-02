#include "teapot.h"

int Teapot::counter=0;
int Teapot::index=0;
Teapot::Teapot()
{
    counter++;
    index++;
    type="teapot";
    name=type+QString::number(index);
    delete list_ltem;
    list_ltem =new QListWidgetItem(name);
}

//void Teapot::draw()
//{
//    glPushMatrix();
//        glTranslatef(position[0],position[1],position[2]);
//        set_glMaterial();
//       // glScalef(scaleX,scaleY,scaleZ);
//        glScalef(scale[0],scale[1],scale[2]);
//        glutSolidTeapot(size);
//        //glutSolidCube(1);

//        glPopMatrix();
//}

//void Teapot::draw_current()
//{
//    glPushMatrix();
//        glTranslatef(position[0],position[1],position[2]);
//        set_glMaterial();
//        glScalef(current_scale,current_scale,current_scale);
//        glScalef(scale[0],scale[1],scale[2]);// glScalef(scaleX,scaleY,scaleZ);
//        glutWireTeapot(size);
//        //glutSolidCube(1);

//        glPopMatrix();
//        draw();
//}

void Teapot::just_draw_yourself(double size, bool isCurrent)
{
    glutSolidTeapot(size);
    if(isCurrent)
    {
        glScalef(current_scale,current_scale,current_scale);
        glutWireTeapot(size);
    }
}



Teapot::~Teapot()
{
    counter--;
}
