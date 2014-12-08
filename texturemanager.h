#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <GL/glut.h>
#include <map>
#pragma pack(2)

#define _CRT_SECURE_NO_WARNINGS
#define BITMAP_ID 0x4D42
#define BYTE  unsigned char
#define DWORD  unsigned int
#define LONG  int
#define UINT  unsigned int
#define WORD  unsigned short int

typedef struct tagBITMAPFILEHEADER {
  WORD    bfType;
  DWORD   bfSize;
  WORD    bfReserved1;
  WORD    bfReserved2;
  DWORD   bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
  DWORD  biSize;
  LONG   biWidth;
  LONG   biHeight;
  WORD   biPlanes;
  WORD   biBitCount;
  DWORD  biCompression;
  DWORD  biSizeImage;
  LONG   biXPelsPerMeter;
  LONG   biYPelsPerMeter;
  DWORD  biClrUsed;
  DWORD  biClrImportant;
} BITMAPINFOHEADER;

class textureManager
{
    static std::map<std::string, GLuint> textureIndex;
    static GLuint * textureArray;
    static int textureCount;
    static int objectCount;
public:
    textureManager(int maxNum);
    textureManager();
    ~textureManager();
    unsigned char *loadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
    int loadTexture(const std::string &filename);
    void bindTexture(int textureid);
    void loadAndbind(const std::string &filename);
};

#endif // TEXTUREMANAGER_H
