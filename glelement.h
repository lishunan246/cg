#ifndef GLELEMENT_H
#define GLELEMENT_H
#include <QGLWidget>
#include <GL/glut.h>
#include <QListWidgetItem>
#include <QtXml>

class GLElement
{
protected:
    static int counter;
    const static float current_scale=1.02;

    GLfloat color[4];
    GLfloat ambient_color[4];
    GLfloat specular_color[4];
    GLfloat diffuse_color[4];

    GLfloat position[3];
    GLfloat scale[3];
    GLdouble size;
    QString type,name;
    QListWidgetItem* list_ltem;

    void set_glMaterial();
public:

    GLElement();

    virtual void from_xml(QDomElement dom);
    //draw the element
    virtual void draw()=0;
    //draw the element when it is selected
    virtual void draw_current()=0;
    QListWidgetItem* getlistltem();
    //void set_color(GLfloat* color4);
    void set_color(GLfloat* color4,bool is_diffuse=true,bool is_specular=true,bool is_ambient=true);
    void set_position(GLfloat* position3);
    void set_scale(GLfloat* scale3);
    void set_size(GLdouble s);

    QDomElement to_xml(QDomDocument* doc);
    virtual ~GLElement();
};

#endif // GLELEMENT_H
