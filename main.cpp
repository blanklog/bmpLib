#include <iostream>
//#include "bmpLibGlobal.h"

using namespace std;

 int saveBMP(const unsigned char *data,int width,int height,int channel,  const char* path);
unsigned char* loadBMP( int *width, int *height, int *channel, const char * path);


int saveBMP_RGB(const unsigned char *data,int width,int height,int channel,  const char* path);
unsigned char* loadBMP_RGB(int *width, int *height, int *channel, const char * path);


int main()
{
    uint8_t *image=new uint8_t[401*400*3];
    int width=400;
    // 填充 QImage 实例
    for (int y = 0; y < 400; ++y) {
        for (int x = 0; x < width; ++x) {
            int index=(x*width+y)*3;
            image[index]=x;
            image[index+1]=y;
            image[index+2]=0;
        }
    }

    saveBMP_RGB(image,width,400,3,"./bmpLibExample.bmp");
    cout << "Hello World!" << endl;
    return 0;
}
