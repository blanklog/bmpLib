#ifndef BMPLIBGLOBAL_H
#define BMPLIBGLOBAL_H


#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define Q_DECL_EXPORT __declspec(dllexport)
#  define Q_DECL_IMPORT __declspec(dllimport)
#else
#  define Q_DECL_EXPORT     __attribute__((visibility("default")))
#  define Q_DECL_IMPORT     __attribute__((visibility("default")))
#endif

#if defined(BMPLIB_LIBRARY)
#  define BMPLIB_EXPORT Q_DECL_EXPORT
#else
#  define BMPLIB_EXPORT Q_DECL_IMPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif


Q_DECL_EXPORT int saveBMP(const unsigned char *data,int width,int height,int channel,  const char* path);
Q_DECL_EXPORT unsigned char* loadBMP( int *width, int *height, int *channel, const char * path);
Q_DECL_EXPORT int saveBMP_RGB(const unsigned char *data,int width,int height,int channel,  const char* path);
Q_DECL_EXPORT unsigned char* loadBMP_RGB(int *width, int *height, int *channel, const char * path);


#ifdef __cplusplus
}
#endif


#endif // BMPLIBGLOBAL_H
