#ifndef GLELEMENT_H
#define GLELEMENT_H
#include <QGLWidget>
#include <GL/glut.h>
#include <QListWidgetItem>
#include <QtXml>

class GLElement
{
protected:
    const static float current_scale=1.02;

    GLfloat color[4];
    GLfloat position[3];
    GLdouble size;
    QString type;
    QListWidgetItem* list_ltem;
public:

    GLElement();

    virtual void from_xml(QDomElement dom);
    //draw the element
    virtual void draw()=0;
    //draw the element when it is selected
    virtual void draw_current()=0;
    QListWidgetItem* getlistltem();
    void set_color(GLfloat* color4);
    void set_position(GLfloat* position3);
    void set_size(GLdouble s);

    QDomElement to_xml(QDomDocument* doc);
    virtual ~GLElement();
};

#endif // GLELEMENT_H
