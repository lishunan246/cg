#include "glelement.h"

int GLElement::counter=0;

void GLElement::set_glMaterial()
{
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse_color);
}

GLElement::GLElement()
{
    counter++;
    type="GLElement";
    size=1;
    for(int i=0;i<4;i++)
    {
        diffuse_color[i]=1.0f;
        ambient_color[i]=1.0f;
        specular_color[i]=1.0f;
        //color[i]=1.0f;
    }
    for(int i=0;i<3;i++)
    {
        position[i]=0.0f;
        scale[i]=1.0f;
    }

    list_ltem =new QListWidgetItem(type+QString::number(counter));
}

QListWidgetItem* GLElement::getlistltem()
{
    return list_ltem;
}

void GLElement::set_color(GLfloat *color4, bool is_diffuse, bool is_specular, bool is_ambient)
{
    if(is_diffuse)
    {
        for(int i=0;i<4;i++)
        {
            this->diffuse_color[i]=*(color4+i);
        }
    }
    if(is_specular)
    {
        for(int i=0;i<4;i++)
        {
            this->specular_color[i]=*(color4+i);
        }
    }
    if(is_ambient)
    {
        for(int i=0;i<4;i++)
        {
            this->ambient_color[i]=*(color4+i);
        }
    }
}



void GLElement::set_position(GLfloat *position3)
{
    for(int i=0;i<3;i++)
    {
        this->position[i]=*(position3+i);
    }
}

void GLElement::set_scale(GLfloat *scale3)
{
    for(int i=0;i<3;i++)
    {
        this->scale[i]=*(scale3+i);
    }
}

void GLElement::set_size(GLdouble s)
{
    size=s;
}

void GLElement::from_xml(QDomElement dom)
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
                this->ambient_color[i]=v.toDouble();
                this->diffuse_color[i]=v.toDouble();
                this->specular_color[i]=v.toDouble();
            }
        }
        else if(element.tagName()=="ambient_colors")
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
                this->ambient_color[i]=v.toDouble();
            }
        }
        else if(element.tagName()=="diffuse_colors")
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
                this->diffuse_color[i]=v.toDouble();
            }
        }
        else if(element.tagName()=="specular_colors")
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
                this->specular_color[i]=v.toDouble();
            }
        }
        else if(element.tagName()=="scales")
        {
            QDomNode nodes[3];
            nodes[0]=node.firstChild();
            nodes[1]=nodes[0].nextSibling();
            nodes[2]=nodes[1].nextSibling();
            for(int i=0;i<3;i++)
            {
                QDomElement e=nodes[i].toElement();
                QString v=e.attribute("value");
                this->scale[i]=v.toDouble();
            }
        }
        else
        {

        }
        node=node.nextSibling();
    }
}

void GLElement::draw()
{
    glPushMatrix();
    glTranslatef(position[0],position[1],position[2]);
    set_glMaterial();

    glScalef(scale[0],scale[1],scale[2]);
    just_draw_yourself(size,false);

    glPopMatrix();
}

void GLElement::draw_current()
{
    glPushMatrix();
    glTranslatef(position[0],position[1],position[2]);
    set_glMaterial();

    glScalef(scale[0],scale[1],scale[2]);
    just_draw_yourself(size,true);

    glPopMatrix();
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

    QDomElement scales=doc->createElement("scales");
    element.appendChild(scales);

    for(int i=0;i<3;i++)
    {
        QDomElement node=doc->createElement("scale");
        node.setAttribute("index",QString::number(i));
        node.setAttribute("value",scale[i]);
        scales.appendChild(node);
    }

    QDomElement colors=doc->createElement("colors");
    element.appendChild(colors);

    for(int i=0;i<4;i++)
    {
        QDomElement node=doc->createElement("specular_color");
        node.setAttribute("index",QString::number(i));
        node.setAttribute("value",specular_color[i]);
        colors.appendChild(node);
    }

    for(int i=0;i<4;i++)
    {
        QDomElement node=doc->createElement("diffuse_color");
        node.setAttribute("index",QString::number(i));
        node.setAttribute("value",diffuse_color[i]);
        colors.appendChild(node);
    }

    for(int i=0;i<4;i++)
    {
        QDomElement node=doc->createElement("ambient_color");
        node.setAttribute("index",QString::number(i));
        node.setAttribute("value",ambient_color[i]);
        colors.appendChild(node);
    }
    return element;
}

GLElement::~GLElement()
{
    delete list_ltem;
    counter--;
}
