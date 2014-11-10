#include "glelement.h"

GLElement::GLElement()
{
    for(int i=0;i<4;i++)
    {
        color[i]=1.0f;
    }
}

void GLElement::draw()
{
    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
        glutSolidTeapot(1);

    glPopMatrix();
}

void GLElement::set_color(GLfloat *color3)
{
    for(int i=0;i<4;i++)
    {
        this->color[i]=*(color3+i);
    }
}
