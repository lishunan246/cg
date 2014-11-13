#include "glwidget.h"
#include <GL/glu.h>
#include <QInputDialog>
#include <QImage>
#include <QMessageBox>
#include <QDateTime>
#include "glelement.h"
#include "mainwindow.h"
#include <QFile>
#include <QtXml>
#include <QDomDocument>
#include <QFileDialog>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    eye[0]=eye[1]=eye[2]=thing[1]=thing[2]=thing[0]=0;
    eye[2]=5;
    rotate=0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(50);
}

QDomElement GLWidget::to_xml(QDomDocument *doc)
{
    QDomElement root=doc->createElement("GLWidget");


    QDomElement eyes=doc->createElement("eyes");
    root.appendChild(eyes);

    for(int i=0;i<3;i++)
    {
        QDomElement node=doc->createElement("eye");
        node.setAttribute("index",QString::number(i));
        node.setAttribute("value",eye[i]);
        eyes.appendChild(node);
    }

    QDomElement things=doc->createElement("things");
    root.appendChild(things);

    for(int i=0;i<3;i++)
    {
        QDomElement node=doc->createElement("thing");
        node.setAttribute("index",QString::number(i));
        node.setAttribute("value",thing[i]);
        things.appendChild(node);
    }

    QDomElement glelements=doc->createElement("GLElements");
    root.appendChild(glelements);

    for (std::vector<GLElement*>::iterator it = v.begin(); it != v.end(); ++it)
    {
       QDomElement node=(*it)->to_xml(doc);
       glelements.appendChild(node);
    }

    return root;
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

void GLWidget::rotate_left()
{
    rotate-=10;
}

void GLWidget::rotate_right()
{
    rotate+=10;
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

void GLWidget::set_color()
{
    bool ok;
    GLfloat temp[4];

    if(currentElement==NULL)
    {
       MainWindow::alert("No element selected");
       return;
    }

    for(int i=0;i<4;i++)
    {
        double color = QInputDialog::getDouble(0, tr("Input color value"),
                tr("Value:"), 1.00, 0, 1, 2, &ok);
        if (ok)
            temp[i]=(float)color;
        else
            return;
    }
    currentElement->set_color(temp);
    updateGL();
}

void GLWidget::set_position()
{
    bool ok;
    GLfloat temp[4];

    if(currentElement==NULL)
    {
        MainWindow::alert("No element selected");
        return;
    }

    for(int i=0;i<3;i++)
    {
        double t = QInputDialog::getDouble(0, tr("Input position value"),
                tr("Value:"), 0.00, -10000, 10000, 2, &ok);
        if (ok)
            temp[i]=(float)t;
        else
            return;
    }
    currentElement->set_position(temp);
    updateGL();
}

void GLWidget::set_size()
{
    bool ok;
    GLdouble temp;

    if(currentElement==NULL)
    {
        MainWindow::alert("No element selected");
        return;
    }

   double t = QInputDialog::getDouble(0, tr("Input position value"),
                tr("Value:"), 1.00, -10000, 10000, 2, &ok);
   if (ok)
       temp=(float)t;
   else
       return;
    currentElement->set_size(temp);
    updateGL();
}

void GLWidget::set_current(QListWidgetItem *l)
{
    int found=0;
    for (std::vector<GLElement*>::iterator it = v.begin(); it != v.end(); ++it)
    {
        if((*it)->getlistltem()==l)
        {
            currentElement=*it;
            found=1;
        }
    }
    if(found==0)
        currentElement=NULL;
}

void GLWidget::screenshot()
{
    QDateTime dt=QDateTime::currentDateTime();
    QString filename=dt.toString(Qt::ISODate);
    filename.append(".jpg");
    updateGL();
    QImage pic;
    pic=grabFrameBuffer();
    pic.save(filename);

    filename.append(" saved!");
    MainWindow::alert(filename);

}

void GLWidget::add_teapot()
{
    GLElement* teapot=new GLElement(this);
    currentElement=teapot;
    std::vector<GLElement*>::iterator i=v.begin();
    v.insert(i,currentElement);

    emit glelement_added(currentElement->getlistltem());
}

void GLWidget::delete_element()
{
    if(currentElement==NULL)
    {
        MainWindow::alert("No element selected");
        return;
    }


    for (std::vector<GLElement*>::iterator it = v.begin(); it != v.end(); )
    {
        if(currentElement==*it)
        {
            it=v.erase(it);
            delete currentElement;
            break;
        }
        else
            ++it;
    }

   if(v.size())
   {
       std::vector<GLElement*>::iterator it = v.begin();
       currentElement=*it;
       emit glelement_selected(currentElement->getlistltem());
   }
   else
   {
       return;
   }
}

void GLWidget::savetofile()
{
    QDomDocument document;
    QDomElement root=this->to_xml(&document);
    document.appendChild(root);


    QStringList fileNames;
    QFileDialog dialog(0);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("XML Files (*.xml)"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    //dialog maybe cancelled
    if(fileNames.count()==0)
        return;

    QString filename=fileNames.at(0);

    if(!filename.endsWith(".xml",Qt::CaseInsensitive))
        filename=filename+".xml";
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        MainWindow::alert("Fail to open file!");
    }
    else
    {
        QTextStream stream(&file);
        stream<<document.toString();
        file.close();
        MainWindow::alert("Saved!");
    }
}

void GLWidget::clear()
{
    currentElement=NULL;
    for (std::vector<GLElement*>::iterator it = v.begin(); it != v.end(); ++it)
    {
        GLElement* t= *it;
        if(t==NULL)
            delete t;
    }

    v.clear();
}

void GLWidget::initializeGL()
{
    glClearColor(0.2,0.2,0.2,1);
    glShadeModel(GL_FLAT);
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
    glRotatef(rotate,0,1,0);

    for (std::vector<GLElement*>::iterator it = v.begin(); it != v.end(); ++it)
    {
        if(*it==NULL)
            continue;
        if(currentElement==*it)
            (*it)->draw_current();
        else
            (*it)->draw();
    }

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


