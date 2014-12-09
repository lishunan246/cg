#ifndef _H_LOADOBJ
#define _H_LOADOBJ
#include "mainwindow.h"
#include <string.h>
#include <vector>
#include <fstream>
#include <iostream>
#include "vertice.h"
#include "mtllib.h"
#include "glelement.h"

#define Header_max 64

using namespace std;




//OBJ
class LoadObj
{
public:

    LoadObj(FILE * fptr);
    ~LoadObj();
    void pushVertex(vertex v);
    void pushNormal(normal n);
    void pushUV(uv u);
    void pushFacet(facet F);

    vertex getVer(int index);
    normal getNor(int index);
    uv getUV(int index);

    facet getFacet(int index);
    int facet_num();

    bool hasUV();
    bool hasMaterial();

    int Vertexnum()
    {
        return Ver.size();
    }

    int Normalnum()
    {
        return Nor.size();
    }

    int UVnum()
    {
        return UV.size();
    }

public:
    int Vbase;
    int Nbase;
    int Ubase;
    string mtllib;

private:
    //string filePath;
    //string mtllibPath;



    vector<vertex> Ver;
    vector<normal> Nor;
    vector<uv> UV;
    vector<facet> F;
    bool ingoreUV;
    bool ignoreMaterial;
};

void RenderObj(LoadObj &obj, mtllib* lib);


//OBJS
class LoadObjs:public GLElement
{
public:
    LoadObjs();
   void  parse();
    ~LoadObjs();
    int size();
    LoadObj getObj(int index);
    mtllib* getmtllib()
    {
        return lib;
    }
    void just_draw_yourself(double size,bool isCurrent);
    void from_xml(QDomElement dom);
    QDomElement to_xml(QDomDocument* doc);


public:
    int hasmtllib;
    string filepath;
    string mtllibpath;
    bool needtoselect;
private:
    static int counter;
    static int index;

    int num;

    vector<LoadObj> Obj;
    mtllib* lib;
};


//void RenderObjs(LoadObjs& objs);

//draw obj ,derived from GLEMENT
/*
class Obj:public GLElement
{
private:
    LoadObj * myobj;
    mtllib* lib;
public:
    Obj(LoadObj  myobj,mtllib *lib);
    void just_draw_yourself(double size,bool isCurrent);
    ~Obj()
    {
    }
};
*/
#endif
