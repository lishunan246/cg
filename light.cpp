#include "light.h"

Light::Light(int name)
{
    Q_ASSERT(name>=0&&name<=7);
    switch (name) {
    case 0:
        this->name=GL_LIGHT0;
        break;
    case 1:
        this->name=GL_LIGHT1;
        break;
    case 2:
        this->name=GL_LIGHT2;
        break;
    case 3:
        this->name=GL_LIGHT3;
        break;
    case 4:
        this->name=GL_LIGHT4;
        break;
    case 5:
        this->name=GL_LIGHT5;
        break;
    case 6:
        this->name=GL_LIGHT6;
        break;
    case 7:
        this->name=GL_LIGHT7;
        break;
    }
}

void Light::enable()
{
    isEnabled=true;
}

void Light::disable()
{
    isEnabled=false;
}

void Light::draw()
{
    glLightfv(name,GL_SPECULAR,specular_color);
    glLightfv(name,GL_AMBIENT,ambient_color);
    glLightfv(name,GL_DIFFUSE,diffuse_color);
    glLightfv(name,GL_POSITION,position);
    glLightf(name,GL_SPOT_CUTOFF,cutoff);
    glLightfv(name,GL_SPOT_DIRECTION,direction);

    if(isEnabled)
        glEnable(name);
    else
        glDisable(name);
}

QDomElement Light::to_xml(QDomDocument *doc)
{

}
