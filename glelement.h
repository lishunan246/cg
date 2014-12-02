#ifndef GLELEMENT_H
#define GLELEMENT_H
#include <QGLWidget>
#include <GL/glut.h>
#include <QListWidgetItem>
#include <QtXml>
#include "xmlhelper.h"
class GLElement
{
protected:
    static int counter;
    static int index;
    const float current_scale=1.02;

    GLfloat position[3];
    GLfloat scale[3];
    GLdouble size;
    int shininess;
    GLdouble rotate_angle,rotate_speed;
    QString type,name;
    QListWidgetItem* list_ltem;

    void set_glMaterial();
    virtual void just_draw_yourself(double size,bool isCurrent)=0;

public:
    GLfloat ambient_color[4];
    GLfloat specular_color[4];
    GLfloat diffuse_color[4];

    GLElement();

    virtual void from_xml(QDomElement dom);
    //draw the element
    virtual void draw();
    //draw the element when it is selected
    virtual void draw_current();
    QListWidgetItem* getlistltem();
    //void set_color(GLfloat* color4);
    void set_color(GLfloat* color4,bool is_diffuse=true,bool is_specular=true,bool is_ambient=true);
    void set_position(GLfloat* position3);
    void set_scale(GLfloat* scale3);
    void set_size(GLdouble s);
    void set_shininess(int s);
    void set_rotate_angle(double angle);
    void set_rotate_speed(double speed);

    virtual QDomElement to_xml(QDomDocument* doc);
    virtual ~GLElement();
};

#endif // GLELEMENT_H
