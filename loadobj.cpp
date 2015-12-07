#include "loadobj.h"
#include "mtllib.h"

//@ZJU_ZT
//Goal : to load a obj file,storing information in the structure we defined

/*
Obj::Obj(LoadObj myobj, mtllib * lib)
{
    this->myobj = myobj;
    this->lib = lib;
    counter++;
    index++;
    type="obj";
    name=type+QString::number(index);
    delete list_ltem;
    list_ltem =new QListWidgetItem(name);
}

void Obj::just_draw_yourself(double size, bool isCurrent)
{
    RenderObj(myobj,lib);
}
*/


//
LoadObj::LoadObj(FILE * fptr)
{
    this->Ubase = 0;
    this->Nbase = 0;
    this->Vbase = 0;
    this->ingoreUV = true;
    this->ignoreMaterial = true;                //default : no material infomation

    char header[Header_max];  // v vn vt f
    //float temp[3];

    while (fscanf(fptr, "%s", header)!=EOF)
    {
        //char temp_path[32];

        if (!strcmp(header, "v"))            //vertex
        {
            vertex temp_v;
            fscanf(fptr, "%f %f %f\n", &temp_v.v[0], &temp_v.v[1], &temp_v.v[2]);
            pushVertex(temp_v);
        }
        else if (!strcmp(header, "vn"))     //normal
        {
            normal temp_n;
            fscanf(fptr, "%f %f %f\n", &temp_n.n[0], &temp_n.n[1], &temp_n.n[2]);
            //cout << temp_n.n[0] << " " << temp_n.n[1] <<" "<< temp_n.n[2] << endl;
            pushNormal(temp_n);
        }
        else if (!strcmp(header, "vt"))     //UV
        {
            if (ingoreUV)
                ingoreUV = false;            //has UV
            uv temp_uv;
            fscanf(fptr, "%f %f\n", &temp_uv.uv[0], &temp_uv.uv[1]);
            pushUV(temp_uv);
        }
        else if (!strcmp(header, "f"))        //facet
        {
            facet temp_f;
            if (ingoreUV)
            {
                fscanf(fptr, "%d//%d %d//%d %d//%d\n", &temp_f.vertexindex[0], &temp_f.normalindex[0], &temp_f.vertexindex[1], &temp_f.normalindex[1], &temp_f.vertexindex[2], &temp_f.normalindex[2]);
            }
            else
            {
                fscanf(fptr, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &temp_f.vertexindex[0], &temp_f.uvindex[0], &temp_f.normalindex[0], &temp_f.vertexindex[1], &temp_f.uvindex[1], &temp_f.normalindex[1], &temp_f.vertexindex[2], &temp_f.uvindex[2], &temp_f.normalindex[2]);  // append uv coordinate
            }

            pushFacet(temp_f);
        }
        else if (!strcmp(header, "usemtl"))    //has material
        {
            char temp[32];
            fscanf(fptr, "%s\n", temp);
            mtllib = temp;
            this->ignoreMaterial = false;
        }
        else if (!strcmp(header, "o"))     //next object
        {
            char vacant[512];
            fgets(vacant, sizeof(vacant), fptr);
            break;
        }
        else              //irrecongizable
        {
            char vacant[512];
            fgets(vacant, sizeof(vacant), fptr);
        }
    }
    //fclose(fptr);
}

LoadObj::~LoadObj()
{

}

void LoadObj::pushVertex(vertex v)
{
    Ver.push_back(v);
}

void LoadObj::pushNormal(normal n)
{
    Nor.push_back(n);
}

void LoadObj::pushUV(uv u)
{
    UV.push_back(u);
}

void LoadObj::pushFacet(facet f)
{
    F.push_back(f);
}

facet LoadObj::getFacet(int index)
{
    //if (index >= 0 && index<F.size())
        return F[index];
}

int LoadObj::facet_num()
{
    return F.size();
}

vertex LoadObj::getVer(int index)
{
    //if (index >= 0 && index<F.size())
        return Ver[index];
}

normal LoadObj::getNor(int index)
{
    //if (index >= 0 && index<F.size())
        return Nor[index];
}

uv LoadObj::getUV(int index)
{
    //if (index >= 0 && index<F.size())
        return UV[index];
}

bool LoadObj::hasUV()
{
    return !ingoreUV;
}

bool LoadObj::hasMaterial()
{
    return !ignoreMaterial;
}



//Render Obj
void RenderObj(LoadObj& obj, mtllib* lib)
{

    glPushMatrix();
    //cout << obj.mtllib << endl;

    if(obj.hasMaterial())    //if this object has material,then render it
    {
        mtl material = lib->getmtlbyName(obj.mtllib);

        //cout << material.Ka[0] << endl;


        glMaterialfv(GL_FRONT, GL_AMBIENT, material.Ka);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material.Kd);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material.Ks);
        glMaterialfv(GL_FRONT, GL_SHININESS, &material.Ns);
    }



    glBegin(GL_TRIANGLES);
    //cout << obj.facet_num() << endl;
    for (int i = 0; i < obj.facet_num(); i++)
    {
        //if (i==3||i==11)

        int n_index = obj.getFacet(i).normalindex[0];
        n_index = n_index - obj.Nbase - 1;
        glNormal3f(obj.getNor(n_index).n[0], obj.getNor(n_index).n[1], obj.getNor(n_index).n[2]);   //normal
        //if (i==9||i==5||i==3||i==11)
        for (int j = 0; j < 3; j++)
        {
            int v_index = obj.getFacet(i).vertexindex[j];

            int uv_index = obj.getFacet(i).uvindex[j];
            v_index = v_index - obj.Vbase - 1;

            uv_index = uv_index - obj.Ubase - 1;


            if (obj.hasUV())
                glTexCoord2f(obj.getUV(uv_index).uv[0], obj.getUV(uv_index).uv[1]);                    //UV
            glVertex3f(obj.getVer(v_index).v[0], obj.getVer(v_index).v[1], obj.getVer(v_index).v[2]);     //vertex

            //cout << "V:" << obj.getVer(v_index).v[0] << " " << obj.getVer(v_index).v[1] << " " << obj.getVer(v_index).v[2] << endl;
            //if (i==1||i==3)
                //cout << "N:" << obj.getNor(n_index).n[0] << " " << obj.getNor(n_index).n[1] << " " << obj.getNor(n_index).n[2] << endl;
        }

        //system("pause");
    }
    glEnd();
    glPopMatrix();
}


int LoadObjs::counter = 0;
int LoadObjs::index=0;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LoadObjs::LoadObjs(string filepath)
{
    this->hasmtllib = false;
    this->num = 0;
    this->filepath = filepath;
    //MainWindow::alert(this->filepath.c_str());
    //FILE * fptr;
    char header[32];
    FILE * fptr = fopen(this->filepath.c_str(),"r");


    if (fptr == NULL)
    {
    //cout << "Can't open file" << endl;
     MainWindow::alert("Fail to open objfile!");
    return;
    }

    while (fscanf(fptr, "%s", header) != EOF)
    {
        if (!strcmp(header, "mtllib"))
        {
            this->hasmtllib = true;
            char temp[32];
            fscanf(fptr, "%s\n", temp);
            MainWindow::alert("The obj file you selected contains material infomation,you should then select a material file. ");
            QString filename=MainWindow::open_file("MTL Files (*.mtl)");
            if(filename==NULL)
                return;
            this->mtllibpath = filename.toStdString();
            this-> lib = new mtllib(mtllibpath);
           // break;
        }
        else if (!strcmp(header, "o"))
        {
            char vacant[512];
            fgets(vacant, sizeof(vacant), fptr);
            break;
        }
        else
        {
            char vacant[512];
            fgets(vacant, sizeof(vacant), fptr);
        }
    }
    while (!feof(fptr))
    {
        LoadObj singleobj(fptr);

        if (this->num)     //base offset should be considered
        {
            singleobj.Vbase = (getObj(num - 1).Vbase + getObj(num - 1).Vertexnum());
            singleobj.Nbase = (getObj(num - 1).Nbase + getObj(num - 1).Normalnum());
            singleobj.Ubase = (getObj(num - 1).Ubase + getObj(num - 1).UVnum());
        }
        Obj.push_back(singleobj);
        this->num++;
    }
    fclose(fptr);
    counter++;
    index++;
    type="obj";
    name=type+QString::number(index);
    delete list_ltem;
    list_ltem =new QListWidgetItem(name);
}


LoadObjs::~LoadObjs()
{
    counter--;
    if(hasmtllib)
        delete lib;
}

void LoadObjs::just_draw_yourself(double size, bool isCurrent)     //to be fixed
{
    //RenderObjs(Obj);
    for (int i = 0; i < Obj.size(); i++)
    {

        //RenderObj(objs.getObj(i),objs.getmtllib());
       // Obj myobj(Obj[i],lib);
        //myobj.just_draw_yourself(0,0);
        RenderObj(Obj[i],lib);
}

}
int LoadObjs::size()
{
    return Obj.size();
}    //return the number of the objects

LoadObj LoadObjs::getObj(int index)   //return obj by index
{
    //if (index >= 0 && index<Obj.size())
        return Obj[index];
}

/*
void RenderObjs(LoadObjs& objs)
{
    for (int i = 0; i < objs.size(); i++)
    {

        //RenderObj(objs.getObj(i),objs.getmtllib());
        Obj myobj(objs.getObj(i),objs.getmtllib());
        myobj.just_draw_yourself(0,0);
    }
}
*/

