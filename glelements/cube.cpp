#include "cube.h"

Cube::Cube()
{
    type="cube";
    delete list_ltem;
    list_ltem =new QListWidgetItem(type);
}

void Cube::draw()
{
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
       // glScalef(scaleX,scaleY,scaleZ);

        glutSolidCube(size);

        glPopMatrix();
}

void Cube::draw_current()
{
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
       glScalef(current_scale,current_scale,current_scale);
       glutWireCube(size);

       glPopMatrix();
       draw();
}

Cube::~Cube()
{

}
