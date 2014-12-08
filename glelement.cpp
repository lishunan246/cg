#include "glelement.h"
#include <iostream>

int GLElement::counter=0;

void GLElement::set_glMaterial()
{
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse_color);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shininess);
}

GLElement::GLElement()
{
    counter++;
    type="GLElement";
    size=1.0;
    shininess=0;
    rotate_angle=0.0;
    rotate_speed=0.0;
    textureidx = -1;

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

void GLElement::cal_normal_vector(GLfloat * result, const float a[3], const float b[3])
{
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
    double lengthOfVector = sqrt(result[0] * result[0] + result[1] * result[1] + result[2] * result[2]);
    result[0] = result[0] / lengthOfVector;
    result[1] = result[1] / lengthOfVector;
    result[2] = result[2] / lengthOfVector;
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

void GLElement::set_shininess(int s)
{
    shininess=s;
}

void GLElement::set_rotate_angle(double angle)
{
    rotate_angle=angle;
}

void GLElement::set_rotate_speed(double speed)
{
    rotate_speed=speed;
}

void GLElement::set_texture_idx(int idx)
{
    textureidx = idx;
}

void GLElement::from_xml(QDomElement dom)
{
    XMLHelper::getAttribute(&dom,"size",&size);
    XMLHelper::getAttribute(&dom,"rotate_speed",&rotate_speed);
    XMLHelper::getAttribute(&dom,"rotate_angle",&rotate_angle);
    XMLHelper::getAttribute(&dom,"shininess",&shininess);

    QDomNode node=dom.firstChild();
    while(!node.isNull())
    {
        XMLHelper::from_xml(&node,"position",position,3);
        XMLHelper::from_xml(&node,"scale",scale,3);
        XMLHelper::from_xml(&node,"ambient_color",ambient_color,4);
        XMLHelper::from_xml(&node,"specular_color",specular_color,4);
        XMLHelper::from_xml(&node,"diffuse_color",diffuse_color,4);

        node=node.nextSibling();
    }
}

void GLElement::draw()
{
    glPushMatrix();
    glTranslatef(position[0],position[1],position[2]);
    set_glMaterial();
    glScalef(scale[0],scale[1],scale[2]);
    rotate_angle+=rotate_speed;
    glRotated(rotate_angle,0,1,0);
    if (textureidx != -1)
    {
        glEnable(GL_TEXTURE_2D);
        textureManager tm;
        tm.bindTexture(textureidx);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }
    just_draw_yourself(size,false);

    glPopMatrix();
}

void GLElement::draw_current()
{
    glPushMatrix();
    glTranslatef(position[0],position[1],position[2]);
    set_glMaterial();
    glScalef(scale[0],scale[1],scale[2]);
    rotate_angle+=rotate_speed;
    glRotated(rotate_angle,0,1,0);
    if (textureidx != -1)
    {
        glEnable(GL_TEXTURE_2D);
        textureManager tm;
        tm.bindTexture(textureidx);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }
    just_draw_yourself(size,true);

    glPopMatrix();
}


QDomElement GLElement::to_xml(QDomDocument *doc)
{
    QDomElement element=doc->createElement(type);
    element.setAttribute("size",size);
    element.setAttribute("rotate_angle",rotate_angle);
    element.setAttribute("rotate_speed",rotate_speed);
    element.setAttribute("shininess",shininess);

    element.appendChild(XMLHelper::to_xml(doc,"position",position,3));
    element.appendChild(XMLHelper::to_xml(doc,"scale",scale,3));
    element.appendChild(XMLHelper::to_xml(doc,"diffuse_color",diffuse_color,4));
    element.appendChild(XMLHelper::to_xml(doc,"ambient_color",ambient_color,4));
    element.appendChild(XMLHelper::to_xml(doc,"specular_color",specular_color,4));

    return element;
}

GLElement::~GLElement()
{
    delete list_ltem;
    counter--;
}
