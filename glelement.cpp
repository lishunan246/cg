#include "glelement.h"
#include <QObject>
GLElement::GLElement(void *parent)
{
    type="teapot";
    for(int i=0;i<4;i++)
    {
        color[i]=1.0f;
    }
    size=1;
    this->parent=parent;
    list_ltem =new QListWidgetItem(type);
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

QListWidgetItem* GLElement::getlistltem()
{
    return list_ltem;
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

GLElement::~GLElement()
{
    delete list_ltem;
}
