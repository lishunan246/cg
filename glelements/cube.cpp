#include "cube.h"

int Cube::counter=0;

Cube::Cube()
{
    counter++;
    type="cube";
    name=type+QString::number(counter);
    delete list_ltem;
    list_ltem =new QListWidgetItem(name);
}

void Cube::draw()
{
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        set_glMaterial();
        glScalef(scale[0],scale[1],scale[2]);

        glutSolidCube(size);

        glPopMatrix();
}

void Cube::draw_current()
{
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        set_glMaterial();
        glScalef(scale[0],scale[1],scale[2]);
       glScalef(current_scale,current_scale,current_scale);
       glutWireCube(size);

       glPopMatrix();
       draw();
}

Cube::~Cube()
{
    counter--;
}
