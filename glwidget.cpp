#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    for(int i=0;i<8;i++)
    {
        l[i]=new Light(i);
    }
    clear();
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(50);
}

void GLWidget::clear()
{
    eye[0]=eye[1]=eye[2]=thing[1]=thing[2]=thing[0]=0;
    eye[2]=5;
    rotate=0;

    currentElement=NULL;

    for (GLElement* e:v)
    {
        if(e!=NULL)
            delete e;
    }
    v.clear();

    for(int i=0;i<8;i++)
    {
        delete l[i];
        l[i]=new Light(i);
    }

    l[0]->enable();
}

QDomElement GLWidget::to_xml(QDomDocument *doc)
{
    QDomElement root=doc->createElement("GLWidget");
    root.setAttribute("rotate",rotate);

    root.appendChild(XMLHelper::to_xml(doc,"eye",eye,3));
    root.appendChild(XMLHelper::to_xml(doc,"thing",thing,3));

    QDomElement glelements=doc->createElement("GLElements");
    root.appendChild(glelements);

    for (GLElement* e:v)
    {
       QDomElement node=e->to_xml(doc);
       glelements.appendChild(node);
    }

    for(Light* light:l)
    {
        QDomElement node=light->to_xml(doc);
        glelements.appendChild(node);
    }

    return root;
}

void GLWidget::from_xml(QDomElement root)
{
    clear();
    XMLHelper::getAttribute(&root,"rotate",&rotate);
    QDomNode n = root.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement(); // try to convert the node to an element(GLWidget)

        if(!e.isNull())
        {
            QString s=e.tagName();

            XMLHelper::from_xml(&n,"eye",eye,3);
            XMLHelper::from_xml(&n,"thing",thing,3);

            if(s=="GLElements")
            {
                QDomNode node=e.firstChild();
                while(!node.isNull())
                {
                    QDomElement element=node.toElement();

                    if(!element.isNull())
                    {
                        if(element.tagName()=="teapot")
                        {
                            Teapot* t= new Teapot();
                            t->from_xml(element);
                            add_element(t);
                        }
                        else if(element.tagName()=="cube")
                        {
                            Cube* c=new Cube();
                            c->from_xml(element);
                            add_element(c);
                        }
                        else if(element.tagName()=="sphere")
                        {
                            Sphere* s=new Sphere();
                            s->from_xml(element);
                            add_element(s);
                        }
                        else if(element.tagName()=="frustum")
                        {
                            Frustum* s=new Frustum();
                            s->from_xml(element);
                            add_element(s);
                        }
                        else if(element.tagName()=="prism")
                        {
                            Prism* s=new Prism();
                            s->from_xml(element);
                            add_element(s);
                        }
                        else if(element.tagName()=="cylinder")
                        {
                            Cylinder* s=new Cylinder();
                            s->from_xml(element);
                            add_element(s);
                        }
                        else if(element.tagName()=="cone")
                        {
                            Cone* s=new Cone();
                            s->from_xml(element);
                            add_element(s);
                        }
                        else if(element.tagName()=="light")
                        {
                            int index=element.attribute("index").toInt();
                            Light* light=new Light(index);
                            light->from_xml(element);
                            delete l[index];
                            l[index]=light;
                        }
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

void GLWidget::config_light()
{
    bool ok;
    int t = QInputDialog::getInt(0, tr("Which light? 0~7"),
                 tr("Value:"), 0,0, 7, 1, &ok);
    Light* p=l[t];
    LightDialog dialog;
    dialog.setLight(p);
    dialog.exec();
}

void GLWidget::left()
{
    eye[0]+=0.5;
    thing[0]+=0.5;
}

void GLWidget::up()
{
    eye[1]-=0.5;
    thing[1]-=0.5;
}

void GLWidget::right()
{
    eye[0]-=0.5;
    thing[0]-=0.5;
}


void GLWidget::down()
{
    eye[1]+=0.5;
    thing[1]+=0.5;
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
}

void GLWidget::zoom_out()
{
    eye[2]+=0.5;
    thing[2]+=0.5;
}

void GLWidget::load_obj()
{
    MainWindow::alert("1");
}

void GLWidget::set_color()
{ 
    if(currentElement==NULL)
    {
       MainWindow::alert("No element selected");
       return;
    }

    ColorDialog dialog;
    dialog.setCurrentElement(currentElement);
    dialog.exec();

    return;
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

void GLWidget::set_scale()
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
        double t = QInputDialog::getDouble(0, tr("Input scale value"),
                tr("Value:"), 1.00, -10000, 10000, 2, &ok);
        if (ok)
            temp[i]=(float)t;
        else
            return;
    }
    currentElement->set_scale(temp);
    updateGL();
}

void GLWidget::set_shininess()
{
    bool ok;
    int temp;

    if(currentElement==NULL)
    {
        MainWindow::alert("No element selected");
        return;
    }

   int t = QInputDialog::getInt(0, tr("Input shininess value"),
                tr("Value:"), 0, 0, 128, 1, &ok);
   if (ok)
       temp=t;
   else
       return;
    currentElement->set_shininess(temp);
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

void GLWidget::set_texture()
{
    MainWindow::alert("textureeeeeeeeeeeeee!");
}

void GLWidget::set_rotate_angle()
{
    bool ok;
    GLdouble temp;

    if(currentElement==NULL)
    {
        MainWindow::alert("No element selected");
        return;
    }

   double t = QInputDialog::getDouble(0, tr("Input rotate angle"),
                tr("Value:"), 1.00, -10000, 10000, 2, &ok);
   if (ok)
       temp=t;
   else
       return;
    currentElement->set_rotate_angle(temp);
    updateGL();
}

void GLWidget::set_rotate_speed()
{
    bool ok;
    GLdouble temp;

    if(currentElement==NULL)
    {
        MainWindow::alert("No element selected");
        return;
    }

   double t = QInputDialog::getDouble(0, tr("Input rotate speed"),
                tr("Value:"), 1.00, -10000, 10000, 2, &ok);
   if (ok)
       temp=t;
   else
       return;
    currentElement->set_rotate_speed(temp);
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
    Teapot* t=new Teapot();
    add_element(t);
}

void GLWidget::add_cube()
{
    Cube* cube=new Cube();
    add_element(cube);
}

void GLWidget::add_cylinder()
{
    Cylinder* c= new Cylinder();
    add_element(c);
}

void GLWidget::add_sphere()
{
    Sphere* sphere=new Sphere();
    add_element(sphere);
}

void GLWidget::add_cone()
{
//    MainWindow::alert("CONE");
    Cone* cone=new Cone();
    add_element(cone);
}

void GLWidget::add_prism()
{
//    MainWindow::alert("PRISM");
    Prism* prism = new Prism();
    add_element(prism);
}

void GLWidget::add_frustum()
{
//    MainWindow::alert("FRUSTUM");
    Frustum* frustum=new Frustum();
    add_element(frustum);
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
}



void GLWidget::initializeGL()
{
    glClearColor(0.2,0.2,0.2,1);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(eye[0],eye[1],eye[2],thing[0],thing[1],thing[2],0,1,0);
    glRotatef(rotate,0,1,0);

    for (GLElement* e:v)
    {
        if(e==NULL)
            continue;
        if(currentElement==e)
            e->draw_current();
        else
            e->draw();
    }

    for(Light* light:l)
    {
        light->draw();
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

void GLWidget::mouseDoubleClickEvent(QMouseEvent * mouse)
{
    int x=mouse->x();
    int y=mouse->y();
    QString s=QString::number(x);
    QString b=QString::number(y);


    get_OGLPos(x,y);

    MainWindow::alert(s+", "+b);
}

void GLWidget::get_OGLPos(int x, int y)
{
    GLint viewport[4];                  // Where The Viewport Values Will Be Stored
    glGetIntegerv(GL_VIEWPORT, viewport);           // Retrieves The Viewport Values (X, Y, Width, Height)

    GLdouble modelview[16];                 // Where The 16 Doubles Of The Modelview Matrix Are To Be Stored
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);       // Retrieve The Modelview Matrix

    GLdouble projection[16];                // Where The 16 Doubles Of The Projection Matrix Are To Be Stored
    glGetDoublev(GL_PROJECTION_MATRIX, projection);     // Retrieve The Projection Matrix

    GLfloat winX, winY, winZ;               // Holds Our X, Y and Z Coordinates
    winX=(float)x;
    winY=(float)y;
    winY=(float)viewport[3]-winY;

    glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    GLdouble posX, posY, posZ;

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    QString q1=QString::number(posX);
    QString q2=QString::number(posY);
    QString q3=QString::number(posZ);

    MainWindow::alert(q1+", "+q2+","+q3);
    return;
}


