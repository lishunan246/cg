
#include "mtllib.h"
#include <iostream>
using namespace std;

mtl::mtl(FILE * fptr)
{
    char header[Header_max];  // newmtl Ns Ka Kd Ks Ni d illum

    while (fscanf(fptr, "%s", header) != EOF)
    {
        //cout << "here:" << header << endl;
        if (!strcmp(header, "newmtl"))
        {
            char temp[32];
            fscanf(fptr,"%s", temp);
            mtl_name = temp;
            //cout << mtl_name << endl;
            //cout << temp << endl;
        }
        else if (!strcmp(header,"Ns"))
        {
            fscanf(fptr,"%f", &Ns);
            //cout << "Ns:" << Ns << endl;
        }
        else if (!strcmp(header, "Ka"))
        {
            fscanf(fptr, "%f %f %f\n", &Ka[0], &Ka[1], &Ka[2]);
            //cout << "Ka:" << Ka[0] << Ka[1] << Ka[2] << endl;
        }
        else if (!strcmp(header, "Kd"))
        {
            fscanf(fptr, "%f %f %f\n", &Kd[0], &Kd[1], &Kd[2]);
            //cout << "Kd:" << Kd[0] << Kd[1] << Kd[2] << endl;
        }
        else if (!strcmp(header, "Ks"))
        {
            fscanf(fptr, "%f %f %f\n", &Ks[0], &Ks[1], &Ks[2]);
            //cout << "Ks:" << Ks[0] << Ks[1] << Ks[2] << endl;
        }
        else if (!strcmp(header, "Ni"))
        {
            fscanf(fptr, "%f\n", &Ni);
            //cout << "Ni:" << Ni << endl;
        }
        else if (!strcmp(header, "d"))
        {
            fscanf(fptr, "%f\n", &d);
            //cout << "d:" << d << endl;
        }
        else if (!strcmp(header, "illum"))
        {
            fscanf(fptr, "%d\n", &illum);
            break;
            //cout << "illum:" << illum << endl;
        }
        /*
        else if (!strcmp(header, ""))
        {
            cout << "hio" << endl;
            break;
        }
        */
        else
        {
            char vacant[512];
            fgets(vacant, sizeof(vacant), fptr);
        }
    }
}

mtl::~mtl()
{

}


mtllib::mtllib(string path)
{
    this->path = path;

    //FILE * fptr;
    char header[32];
    FILE * fptr = fopen(this->path.c_str(), "r");


    if (fptr == NULL)
    {
        //cout << "Can't open file" << endl;
           MainWindow::alert("Fail to open objfile!");
        return;
    }

    while (1)
    {
        char temp[256];
        fgets(temp,sizeof(temp),fptr);
        if (!strcmp(temp, "\n"))
            break;
    }

    while (!feof(fptr))
    {
        mtl m(fptr);
        //cout << "hi" << endl;
        lib.push_back(m);
    }
    fclose(fptr);
}

mtllib::~mtllib()
{

}
