#ifndef _H_MTLLIB
#define _H_MTLLIB
#include "mainwindow.h"
#include <GL/glut.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
#define Header_max 64

const string mtl_append = ".mtl";

class mtl
{
public:
    mtl(FILE * fptr);
    ~mtl();
public:
    string mtl_name;    //material name
    GLfloat Ns;    //r indicator
    GLfloat Ka[3];    //ambient indicator
    GLfloat Kd[3];   //diffuse indicator
    GLfloat Ks[3];  //mirror
    GLfloat Ni;    //
    GLfloat d;    //
    int illum;     //illum
};



class mtllib
{
public:
    mtllib(string path);
    ~mtllib();
    mtl getmtlbyName(string name)
    {
        //cout << name << endl;
        //cout << "++++++++++++++++++" << endl;
        for (int i = 0; i < mtl_num(); i++)
        {
            //cout << lib[i].mtl_name << endl;
            if (lib[i].mtl_name == name)
            {
                //cout << lib[i].mtl_name << endl;
                return lib[i];
            }
        }
    }

    int mtl_num()
    {
        return lib.size();
    }

private:
    string path;
    vector<mtl> lib;
};

#endif
