#include "glelement.h"

GLElement::GLElement(void *parent)
{
    for(int i=0;i<4;i++)
    {
        color[i]=1.0f;
    }
    size=1;
    this->parent=parent;
}

void GLElement::draw()
{
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
       // glScalef(scaleX,scaleY,scaleZ);
        glutSolidTeapot(size);
        //glutSolidCube(1);

    glPopMatrix();
}

void GLElement::set_color(GLfloat *color4)
{
    for(int i=0;i<4;i++)
    {
        this->color[i]=*(color4+i);
    }
}

void GLElement::set_position(GLfloat *position3)
{
    for(int i=0;i<3;i++)
    {
        this->position[i]=*(position3+i);
    }
}

void GLElement::set_size(GLdouble s)
{
    size=s;
}
