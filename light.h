#ifndef LIGHT_H
#define LIGHT_H
#include <QString>
#include "GL/gl.h"
#include <QDomElement>
#include "xmlhelper.h"

class Light
{
private:
    GLenum name;
    int index;
public:
    GLfloat ambient_color[4]={0,0,0,1};
    GLfloat specular_color[4]={1,1,1,1};
    GLfloat diffuse_color[4]={1,1,1,1};
    GLfloat position[4]={0,0,1,0};
    GLfloat direction[3]={0,0,-1};
    GLfloat cutoff=180;
    bool isEnabled=false;


    Light(int name);
    void enable();
    void disable();
    void draw();
    QDomElement to_xml(QDomDocument* doc);
    void from_xml(QDomElement dom);
};

#endif // LIGHT_H
