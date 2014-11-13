#include "glelement.h"
#include <QObject>
GLElement::GLElement(void *parent)
{
    type="teapot";
    size=1;
    for(int i=0;i<4;i++)
    {
        color[i]=1.0f;
    }
    for(int i=0;i<3;i++)
    {
        position[i]=0.0f;
    }

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

void GLElement::draw_current()
{
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
       // glScalef(scaleX,scaleY,scaleZ);
        glutWireTeapot(size);
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

QDomElement GLElement::to_xml(QDomDocument *doc)
{
    QDomElement element=doc->createElement(type);
    element.setAttribute("size",size);

    QDomElement positions=doc->createElement("positions");
    element.appendChild(positions);

    for(int i=0;i<3;i++)
    {
        QDomElement node=doc->createElement("position");
        node.setAttribute("index",QString::number(i));
        node.setAttribute("value",position[i]);
        positions.appendChild(node);
    }

    QDomElement colors=doc->createElement("colors");
    element.appendChild(colors);

    for(int i=0;i<4;i++)
    {
        QDomElement node=doc->createElement("color");
        node.setAttribute("index",QString::number(i));
        node.setAttribute("value",color[i]);
        colors.appendChild(node);
    }
    return element;
}

GLElement::~GLElement()
{
    delete list_ltem;
}
