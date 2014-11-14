#include "glwidget.h"
#include <GL/glu.h>
#include <QInputDialog>
#include <QImage>
#include <QDateTime>
#include "glelement.h"
#include "mainwindow.h"
#include <QFile>
#include <QtXml>
#include <QDomDocument>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    initialize();
    clear();
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(50);
}

void GLWidget::initialize()
{
    eye[0]=eye[1]=eye[2]=thing[1]=thing[2]=thing[0]=0;
    eye[2]=5;
    rotate=0;
}


QDomElement GLWidget::to_xml(QDomDocument *doc)
{
    QDomElement root=doc->createElement("GLWidget");
    root.setAttribute("rotate",rotate);


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

void GLWidget::from_xml(QDomElement root)
{
    initialize();
    clear();
    if(root.hasAttribute("rotate"))
    {
        rotate=root.attribute("rotate").toInt();
    }
    QDomNode n = root.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement(); // try to convert the node to an element(GLWidget)


        if(!e.isNull())
        {
            QString s=e.tagName();

            if(s=="eyes")
            {
                QDomNode nodes[3];
                nodes[0]=n.firstChild();
                nodes[1]=nodes[0].nextSibling();
                nodes[2]=nodes[1].nextSibling();
                for(int i=0;i<3;i++)
                {
                    QDomElement e=nodes[i].toElement();
                    QString v=e.attribute("value");

                    eye[i]=v.toDouble();
                }
            }
            else if(s=="things")
            {
                QDomNode nodes[3];
                nodes[0]=n.firstChild();
                nodes[1]=nodes[0].nextSibling();
                nodes[2]=nodes[1].nextSibling();
                for(int i=0;i<3;i++)
                {
                    QDomElement e=nodes[i].toElement();
                    QString v=e.attribute("value");

                    thing[i]=v.toDouble();
                }
            }

            else if(s=="GLElements")
            {
                QDomNode node=e.firstChild();
                while(!node.isNull())
                {
                    QDomElement element=node.toElement();

                    if(!element.isNull())
                    {
                        GLElement* newobject=GLElement::from_xml(element);

                        add_element(newobject);
                    }

                    node=node.nextSibling();
                }
            }
            //unhandled children type
            else
            {

            }
        }
        n = n.nextSibling();
    }
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

void GLWidget::add_element(GLElement *e)
{
    currentElement=e;
    std::vector<GLElement*>::iterator i=v.begin();
    v.insert(i,e);

    emit glelement_added(e->getlistltem());
}

void GLWidget::add_teapot()
{
    GLElement* teapot=new GLElement();
    add_element(teapot);
}

void GLWidget::delete_current()
{
    if(currentElement==NULL)
    {
        MainWindow::alert("No element selected");
        return;
    }

    delete_element(currentElement);
}

void GLWidget::delete_element(GLElement *e)
{
    for (std::vector<GLElement*>::iterator it = v.begin(); it != v.end(); )
    {
        if(e==*it)
        {
            it=v.erase(it);
            delete e;
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

    QString filename=MainWindow::new_file("XML Files (*.xml)",".xml");

    if(filename==NULL)
        return;

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

void GLWidget::loadfile()
{
    QString filename=MainWindow::open_file("XML Files (*.xml)");
    if(filename==NULL)
        return;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        MainWindow::alert("Fail to open file!");
        return;
    }

    QDomDocument doc;

    if (!doc.setContent(&file))
    {
        MainWindow::alert("Fail to parse!");
        file.close();
        return;
    }

    file.close();

    QDomElement docElem = doc.documentElement();

    from_xml(docElem);

    MainWindow::alert("Load successfully!");
}

void GLWidget::clear()
{
    currentElement=NULL;

    for (std::vector<GLElement*>::iterator it = v.begin(); it != v.end(); ++it)
    {
        if(*it!=NULL)
            delete *it;
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



