#ifndef GLELEMENT_H
#define GLELEMENT_H
#include <QGLWidget>
#include <GL/glut.h>
#include <QListWidgetItem>
#include <QtXml>

class GLElement
{
private:
    GLfloat color[4];
    GLfloat position[3];
    GLdouble size;
    QString type;
    QListWidgetItem* list_ltem;
public:

    GLElement();

    static GLElement* from_xml(QDomElement dom) ;
    //draw the element
    void draw();
    //draw the element when it is selected
    void draw_current();
    QListWidgetItem* getlistltem();
    void set_color(GLfloat* color4);
    void set_position(GLfloat* position3);
    void set_size(GLdouble s);

    QDomElement to_xml(QDomDocument* doc);
    ~GLElement();
};

#endif // GLELEMENT_H
