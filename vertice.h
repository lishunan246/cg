#ifndef _H_VERTICE
#define _H_VERTICE
#include <GL/glut.h>



typedef struct
{
    GLfloat v[3];
}vertex;

typedef struct
{
    GLfloat n[3];
}normal;

typedef struct
{
    GLfloat uv[2];
}uv;

typedef struct
{
    GLint normalindex[3];
    GLint vertexindex[3];
    GLint uvindex[3];
}facet;

/*
typedef GLfloat vertex[3];
typedef GLfloat normal[3];
typedef GLfloat uv[2];
*/
#endif
