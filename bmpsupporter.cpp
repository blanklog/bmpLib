#include "bmpsupporter.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;



int BmpSupporter::saveBMP(const uint8_t *data,int width,int height,int channel,  std::string path) {
        std::fstream fs(path,ios_base::out|ios_base::binary);
        if(!fs.good())
        {
         cout<<"image save failed. at " << __LINE__ << " in" <<__FILE__<<endl;
         return RETURN_ERRO_IO;
        }
        BitMapFileHeader fileHeader;
        BitMapInfoHeader bmpHeader;

        bmpHeader.biWidth=width;
        bmpHeader.biHeight=height;
        bmpHeader.biBitCount=8*channel;
        bmpHeader.biSizeImage=bmpHeader.biWidth*bmpHeader.biHeight*channel;

        fileHeader.bfSize=54+bmpHeader.biSizeImage;
        cout<<sizeof(bmpHeader)<<endl;

        fs.write(reinterpret_cast<const char*>(&fileHeader.bfType),2);
        fs.write(reinterpret_cast<const char*>(&fileHeader.bfSize),4);
        fs.write(reinterpret_cast<const char*>(&fileHeader.bfReserved1),2);
        fs.write(reinterpret_cast<const char*>(&fileHeader.bfReserved2),2);
        fs.write(reinterpret_cast<const char*>(&fileHeader.bfOffBits),4);

        fs.write(reinterpret_cast<const char*>(&bmpHeader),40);
        fs.write(reinterpret_cast<const char*>(data),width*height*channel);

        fs.close();
        return RETURN_OK;
} // namespace simpleBMP


uint8_t* BmpSupporter::loadBMP(int32_t *width, int32_t *height, int *channel, std::string path)
{
    std::fstream fs(path,ios_base::in|ios_base::binary);
    if(!fs.good())
    {
     cout<<"image open failed. at " << __LINE__ << " in" <<__FILE__<<endl;
     return nullptr;
    }
    BitMapFileHeader fileHeader;
    BitMapInfoHeader bmpHeader;


    fs.read(reinterpret_cast<char*>(&fileHeader),14);
    if(!fs || fs.gcount()!=14)
    {
     cout<<"image read failed. at " << __LINE__ << " in" <<__FILE__<<endl;
     return nullptr;
    }

    fs.read(reinterpret_cast<char*>(&bmpHeader),40);
    if(!fs || fs.gcount()!=40)
    {
     cout<<"image read failed. at " << __LINE__ << " in" <<__FILE__<<endl;
     return nullptr;
    }
    if(bmpHeader.biCompression!=0 || bmpHeader.biClrUsed!=0)
    {
        cout<<"image reader unsupport compress image or color-index image."<<endl;
        return nullptr;
    }

    *height=bmpHeader.biHeight;
    *width=bmpHeader.biWidth;
    *channel=bmpHeader.biBitCount/8;
    int dataSize=(*height)*(*width)*(*channel);

    uint8_t *data=(uint8_t*)malloc(dataSize);
    fs.read(reinterpret_cast<char*>(&data),dataSize);
    if( fs.gcount()!=dataSize)
    {
     cout<<"image read failed. at " << __LINE__ << " in" <<__FILE__;
     free(data);
     return nullptr;
    }

    return data;
}

int saveBMP_RGB(const unsigned char *data,int width,int height,int channel,  const char* path)
{
    int size=width*height*channel;
    uint8_t *tmpData=new uint8_t[size];
    for(int i=0;i<size;i+=3)
    {
        tmpData[i]=data[i+2];
        tmpData[i+1]=data[i+1];
        tmpData[i+2]=data[i];
    }
   int ret= BmpSupporter::saveBMP(tmpData,width,height,channel,path);
   delete [] tmpData;
   return ret;
}

unsigned char* loadBMP_RGB(int *width, int *height, int *channel, const char * path)
{
    uint8_t *data=BmpSupporter::loadBMP(width,height,channel,path);
    int size=(*width)*(*height)*(*channel);
    uint8_t *tmpData=(uint8_t*)malloc(size);
    for(int i=0;i<size;i+=3)
    {
        tmpData[i]=data[i+2];
        tmpData[i+1]=data[i+1];
        tmpData[i+2]=data[i];
    }
    free(data);
    return tmpData;
};


int saveBMP(const unsigned char *data,int width,int height,int channel,  const char* path)
{
    return BmpSupporter::saveBMP(data,width,height,channel,path);
}

unsigned char* loadBMP( int *width, int *height, int *channel, const char * path)
{
    return BmpSupporter::loadBMP(width,height,channel,path);
}




