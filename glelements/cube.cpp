#include "cube.h"

int Cube::counter=0;

Cube::Cube()
{
    counter++;
    type="cube";
    name=type+QString::number(counter);
    delete list_ltem;
    list_ltem =new QListWidgetItem(name);
}

void Cube::just_draw_yourself(double size, bool isCurrent)
{
//    glutSolidCube(size);
    solidCube(size);
    if(isCurrent)
    {
        glScalef(current_scale,current_scale,current_scale);
        glutWireCube(size);
    }
}

void Cube::solidCube(double size)
{
    float half = (float) size / 2;
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);	// 给出纹理映射坐标
    glVertex3f(half, half, half);
    glTexCoord2f(0, 1);
    glVertex3f(half, -half, half);
    glTexCoord2f(1, 1);
    glVertex3f(half, -half, -half);
    glTexCoord2f(1, 0);
    glVertex3f(half, half, -half);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex3f(-half, half, half);
    glTexCoord2f(0, 1);
    glVertex3f(-half, -half, half);
    glTexCoord2f(1, 1);
    glVertex3f(-half, -half, -half);
    glTexCoord2f(1, 0);
    glVertex3f(-half, half, -half);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex3f(half, half, half);
    glTexCoord2f(0, 1);
    glVertex3f(-half, half, half);
    glTexCoord2f(1, 1);
    glVertex3f(-half, half, -half);
    glTexCoord2f(1, 0);
    glVertex3f(half, half, -half);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex3f(half, -half, half);
    glTexCoord2f(0, 1);
    glVertex3f(-half, -half, half);
    glTexCoord2f(1, 1);
    glVertex3f(-half, -half, -half);
    glTexCoord2f(1, 0);
    glVertex3f(half, -half, -half);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex3f(half, half, half);
    glTexCoord2f(0, 1);
    glVertex3f(half, -half, half);
    glTexCoord2f(1, 1);
    glVertex3f(-half, -half, half);
    glTexCoord2f(1, 0);
    glVertex3f(-half, half, half);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex3f(half, half, -half);
    glTexCoord2f(0, 1);
    glVertex3f(half, -half, -half);
    glTexCoord2f(1, 1);
    glVertex3f(-half, -half, -half);
    glTexCoord2f(1, 0);
    glVertex3f(-half, half, -half);
    glEnd();
}
//void Cube::draw()
//{
//    glPushMatrix();
//        glTranslatef(position[0],position[1],position[2]);
//        set_glMaterial();
//        glScalef(scale[0],scale[1],scale[2]);

//        glutSolidCube(size);

//        glPopMatrix();
//}

//void Cube::draw_current()
//{
//    glPushMatrix();
//        glTranslatef(position[0],position[1],position[2]);
//        set_glMaterial();
//        glScalef(scale[0],scale[1],scale[2]);
//       glScalef(current_scale,current_scale,current_scale);
//       glutWireCube(size);

//       glPopMatrix();
//       draw();
//}

Cube::~Cube()
{
    counter--;
}
