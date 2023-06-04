#ifndef BMPSUPPORTER_H
#define BMPSUPPORTER_H
#include <cstdint>
#include <string>


class BmpSupporter
{
    struct BitMapFileHeader {
      uint16_t bfType=0x4d42;      // Fixed value,0x4d42
      uint32_t bfSize;             // File size in bytes, usually zero for uncompressed BMP
      uint16_t bfReserved1=0;        // Always zero
      uint16_t bfReserved2=0;        // Always zero
      uint32_t bfOffBits=54;          // File offset to the start of the pixel data
    };

    struct BitMapInfoHeader {
      uint32_t biSize=40;         // Size of this header in bytes, we only support 40
      int32_t biWidth;              // Image width in pixels
      int32_t biHeight;             // Image height in pixels
      uint16_t biPlanes=1;          // Always 1
      uint16_t biBitCount;          // Number of bits per pixel, we only support 8 and 24
      uint32_t biCompression=0;     // Compression type, 0 for uncompressed, usually zero
      uint32_t biSizeImage;       // Used only when biCompression is not 0, usually zero
      int32_t biXPelsPerMeter=1204; // Horizontal resolution in pixels per meter
      int32_t biYPelsPerMeter=1024; // Vertical resolution in pixels per meter
      uint32_t biClrUsed=0;         // Number of colors used
      uint32_t biClrImportant=0;    // Number of important colors
    };

    enum RETUREN_STATE{
        RETURN_OK=0,
        RETURN_ERRO=-1,
        RETURN_ERRO_IO=-2
    };

public:
static int saveBMP(const uint8_t *data,int width,int height,int channel, std::string path);
static uint8_t* loadBMP(int *width,int *height,int * channel, std::string path);

};


#endif // BMPSUPPORTER_H
