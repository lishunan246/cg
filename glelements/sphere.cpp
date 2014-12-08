#include "sphere.h"
int Sphere::counter=0;
int Sphere::index=0;
#define HPI 1.570796327
#define PI 3.141592654
#define DPI 6.283185307
Sphere::Sphere()
{
    counter++;
    index++;
    type="sphere";
    name=type+QString::number(index);
    delete list_ltem;
    list_ltem =new QListWidgetItem(name);
}

void Sphere::just_draw_yourself(double size, bool isCurrent)
{
//    glutSolidSphere(size,100,100);
    solidSphere(size,100,100);
    if(isCurrent)
    {
        glScalef(current_scale,current_scale,current_scale);
        glutWireSphere(size,10,10);
    }
}

void Sphere::solidSphere(double radius, int slices, int stacks)
{
    double vDuration = HPI / stacks;
    double hDuration = DPI / slices;
    float textureDuration = 0.5 / stacks;
    Point * pointArray = new Point[slices + 1];

    for (int i = 0; i < slices + 1; i++)
    {
        pointArray[i].x = 0;
        pointArray[i].y = radius;
        pointArray[i].z = 0;
    }

    glBegin(GL_TRIANGLES);
    float textureHeight = 1;
    for (double vangle = vDuration; vangle < HPI + 0.01; vangle += vDuration, textureHeight -= textureDuration)
    {
        double innerRadius = radius * sin(vangle);
        double innerHeight = radius * cos(vangle);
        int sliceCount = 0;
        for (double hangle = 0; hangle < DPI + 0.01; hangle += hDuration, sliceCount++)
        {
            GLfloat upperCurrent[3] = {pointArray[sliceCount].x, pointArray[sliceCount].y, pointArray[sliceCount].z};
            GLfloat upperNext[3] = {pointArray[sliceCount + 1].x, pointArray[sliceCount + 1].y, pointArray[sliceCount + 1].z};
            GLfloat lowerCurrent[3] = {innerRadius * cos(hangle), innerRadius * sin(hangle), innerHeight};
            GLfloat lowerNext[3] = {innerRadius * cos(hangle + hDuration), innerRadius * sin(hangle + hDuration), innerHeight};

            pointArray[sliceCount].x = lowerCurrent[0];
            pointArray[sliceCount].y = lowerCurrent[1];
            pointArray[sliceCount].z = lowerCurrent[2];

            GLfloat * normal = mean3(upperCurrent, upperNext, lowerCurrent);
            glNormal3fv(normal);
            glTexCoord2f(hangle / DPI, textureHeight);                                  glVertex3fv(upperCurrent);
            glTexCoord2f((hangle + hDuration) / DPI, textureHeight);                    glVertex3fv(upperNext);
            glTexCoord2f(hangle / DPI, textureHeight - textureDuration);                glVertex3fv(lowerCurrent);

            delete [] normal;
            normal = mean3(upperNext, lowerNext, lowerCurrent);
            glNormal3fv(normal);
            glTexCoord2f((hangle + hDuration) / DPI, textureHeight);                    glVertex3fv(upperNext);
            glTexCoord2f((hangle + hDuration) / DPI, textureHeight - textureDuration);  glVertex3fv(lowerNext);
            glTexCoord2f(hangle / DPI, textureHeight - textureDuration);                glVertex3fv(lowerCurrent);
            delete [] normal;
        }
    }
    glEnd();


    for (int i = 0; i < slices + 1; i++)
    {
        pointArray[i].x = 0;
        pointArray[i].y = -radius;
        pointArray[i].z = 0;
    }
    glBegin(GL_TRIANGLES);
    textureHeight = 0;
    for (double vangle = vDuration; vangle < HPI + 0.01; vangle += vDuration, textureHeight += textureDuration)
    {
        double innerRadius = radius * sin(vangle);
        double innerHeight = -radius * cos(vangle);
        int sliceCount = 0;
        for (double hangle = 0; hangle < DPI + 0.01; hangle += hDuration, sliceCount++)
        {
            GLfloat upperCurrent[3] = {pointArray[sliceCount].x, pointArray[sliceCount].y, pointArray[sliceCount].z};
            GLfloat upperNext[3] = {pointArray[sliceCount + 1].x, pointArray[sliceCount + 1].y, pointArray[sliceCount + 1].z};
            GLfloat lowerCurrent[3] = {innerRadius * cos(hangle), innerRadius * sin(hangle), innerHeight};
            GLfloat lowerNext[3] = {innerRadius * cos(hangle + hDuration), innerRadius * sin(hangle + hDuration), innerHeight};

            pointArray[sliceCount].x = lowerCurrent[0];
            pointArray[sliceCount].y = lowerCurrent[1];
            pointArray[sliceCount].z = lowerCurrent[2];

            GLfloat * normal = mean3(upperCurrent, upperNext, lowerCurrent);
            glNormal3fv(normal);
            glTexCoord2f(hangle / DPI, textureHeight);                                  glVertex3fv(upperCurrent);
            glTexCoord2f((hangle + hDuration) / DPI, textureHeight);                    glVertex3fv(upperNext);
            glTexCoord2f(hangle / DPI, textureHeight + textureDuration);                glVertex3fv(lowerCurrent);

            delete [] normal;
            normal = mean3(upperNext, lowerNext, lowerCurrent);
            glNormal3fv(normal);
            glTexCoord2f((hangle + hDuration) / DPI, textureHeight);                    glVertex3fv(upperNext);
            glTexCoord2f((hangle + hDuration) / DPI, textureHeight + textureDuration);  glVertex3fv(lowerNext);
            glTexCoord2f(hangle / DPI, textureHeight + textureDuration);                glVertex3fv(lowerCurrent);
            delete [] normal;
        }
    }
    glEnd();
}

void Sphere::wireSphere(double radius, int slices, int stacks)
{

}

GLfloat *Sphere::mean3(const GLfloat a[], const GLfloat b[], const GLfloat c[])
{
    GLfloat * result = new GLfloat[3];
    result[0] = (a[0] + b[0] + c[0]) / 3;
    result[1] = (a[1] + b[1] + c[1]) / 3;
    result[2] = (a[2] + b[2] + c[2]) / 3;
    return result;
}


Sphere::~Sphere()
{
    counter--;
}
