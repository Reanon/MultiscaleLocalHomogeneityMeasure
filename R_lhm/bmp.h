#ifndef _BMP_H_
#define _BMP_H_
void Threshold(BYTE *img, int width, int height, BYTE Thre);
BYTE *Read8BitBmpFile2Img(const char * filename, int *width, int *height);
int Write8BitImg2BmpFile(BYTE *img, int width, int height, const char * filename);
#endif // !_BMP_H_