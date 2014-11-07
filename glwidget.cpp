#include "glwidget.h"
#include <GL/glu.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    eye[0]=eye[1]=eye[2]=thing[1]=thing[2]=thing[0]=0;
    eye[2]=5;
    rotate=0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(50);
}

void GLWidget::left()
{
    eye[0]+=0.5;
    thing[0]+=0.5;

    updateGL();
}

void GLWidget::up()
{
    eye[1]-=0.5;
    thing[1]-=0.5;

    updateGL();
}

void GLWidget::right()
{
    eye[0]-=0.5;
    thing[0]-=0.5;

    updateGL();
}

void GLWidget::down()
{
    eye[1]+=0.5;
    thing[1]+=0.5;

    updateGL();
}

void GLWidget::zoom_in()
{
    eye[2]-=0.5;
    thing[2]-=0.5;

    updateGL();
}

void GLWidget::zoom_out()
{
    eye[2]+=0.5;
    thing[2]+=0.5;

    updateGL();
}

void GLWidget::initializeGL()
{
    glClearColor(0.2,0.2,0.2,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    GLfloat a[]={1,1,1,1};
    glLightfv(GL_LIGHT1,GL_SPECULAR,a);
    //glLightfv(GL_LIGHT1,GL_AMBIENT,a);

    glEnable(GL_LIGHT1);
//    glEnable(GL_LIGHTING_BIT);
//    glEnable(GL_COLOR_MATERIAL);
}

void GLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(eye[0],eye[1],eye[2],thing[0],thing[1],thing[2],0,1,0);
    glRotatef(rotate,1,1,1);
    rotate+=10;

    GLfloat c[]={1,0.9,0,1};

    //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,c);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,c);
    glutSolidTeapot(1);

}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(h==0)h=1;
    float ratio=(GLfloat)w/(GLfloat)h;

    gluPerspective(45,ratio,0.1,100);
    //gluOrtho(-5,5,-5,5,0,100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


