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
       // glScalef(scaleX,scaleY,scaleZ);
       glutWireCube(size);

       glPopMatrix();
}

void Cube::from_xml(QDomElement dom)
{
    if(dom.tagName()=="cube")
    {


        if(dom.hasAttribute("size"))
        {
            this->size=dom.attribute("size").toDouble();
        }

        QDomNode node=dom.firstChild();
        while(!node.isNull())
        {
            QDomElement element=node.toElement();
            if(element.tagName()=="positions")
            {
                QDomNode nodes[3];
                nodes[0]=node.firstChild();
                nodes[1]=nodes[0].nextSibling();
                nodes[2]=nodes[1].nextSibling();
                for(int i=0;i<3;i++)
                {
                    QDomElement e=nodes[i].toElement();
                    QString v=e.attribute("value");

                    this->position[i]=v.toDouble();
                }
            }
            else if(element.tagName()=="colors")
            {
                QDomNode nodes[3];
                nodes[0]=node.firstChild();
                nodes[1]=nodes[0].nextSibling();
                nodes[2]=nodes[1].nextSibling();
                nodes[3]=nodes[2].nextSibling();
                for(int i=0;i<4;i++)
                {
                    QDomElement e=nodes[i].toElement();
                    QString v=e.attribute("value");

                    this->color[i]=v.toDouble();
                }
            }
            else
            {

            }
            node=node.nextSibling();
        }

    }
}

Cube::~Cube()
{

}
