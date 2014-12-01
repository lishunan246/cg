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
    static GLfloat n[6][3] =
    {
      {-1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0},
      {0.0, 0.0, 1.0},
      {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
      {0, 1, 2, 3},
      {3, 2, 6, 7},
      {7, 6, 5, 4},
      {4, 5, 1, 0},
      {5, 6, 2, 1},
      {7, 4, 0, 3}
    };
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--) {
      glBegin(GL_QUADS);
      glNormal3fv(&n[i][0]);
      glTexCoord2f(0, 0);
      glVertex3fv(&v[faces[i][0]][0]);
      glTexCoord2f(0, 1);
      glVertex3fv(&v[faces[i][1]][0]);
      glTexCoord2f(1, 1);
      glVertex3fv(&v[faces[i][2]][0]);
      glTexCoord2f(1, 0);
      glVertex3fv(&v[faces[i][3]][0]);
      glEnd();
    }
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
