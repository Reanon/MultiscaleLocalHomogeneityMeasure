#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include "bmp.h"
BYTE *Read8BitBmpFile2Img(const char * filename, int *width, int *height)
{
	FILE * BinFile;
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER BmpHeader;
	BYTE *img;
	int size;
	int Suc = 1;

	// Open File
	*width = *height = 0;
	if ((BinFile = fopen(filename, "rb")) == NULL) return NULL;
	// Read Struct Info
	if (fread((void *)&FileHeader, 1, sizeof(FileHeader), BinFile) != sizeof(FileHeader)) Suc = -1;
	if (fread((void *)&BmpHeader, 1, sizeof(BmpHeader), BinFile) != sizeof(BmpHeader)) Suc = -1;
	if (Suc == -1) { fclose(BinFile); return NULL; }
	// Read Image Data
	*width = (BmpHeader.biWidth + 3) / 4 * 4;
	*height = BmpHeader.biHeight;
	size = (BmpHeader.biWidth + 3) / 4 * 4 * BmpHeader.biHeight;
	fseek(BinFile, FileHeader.bfOffBits, SEEK_SET);
	if ((img = new BYTE[size]) != NULL)
	{
		if (fread(img, sizeof(BYTE), size, BinFile) != size)
		{
			fclose(BinFile);
			delete[]img;
			img = NULL;
			return NULL;
		}
	}
	fclose(BinFile);
	return img;
}

int Write8BitImg2BmpFile(BYTE *img, int width, int height, const char * filename)
{
	FILE * BinFile;
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER BmpHeader;
	BYTE p[4];
	int i, Suc = 1;

	// Open File
	if ((BinFile = fopen(filename, "w+b")) == NULL) { return -1; }
	// Fill the FileHeader
	FileHeader.bfType = ((WORD)('M' << 8) | 'B');
	FileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BmpHeader) + 256 * 4L;
	FileHeader.bfSize = FileHeader.bfOffBits + width*height;
	FileHeader.bfReserved1 = 0;
	FileHeader.bfReserved2 = 0;
	if (fwrite((void *)&FileHeader, 1, sizeof(BITMAPFILEHEADER), BinFile) != sizeof(BITMAPFILEHEADER)) Suc = -1;
	// Fill the ImgHeader
	BmpHeader.biSize = 40;
	BmpHeader.biWidth = width;
	BmpHeader.biHeight = height;
	BmpHeader.biPlanes = 1;
	BmpHeader.biBitCount = 8;
	BmpHeader.biCompression = 0;
	BmpHeader.biSizeImage = 0;
	BmpHeader.biXPelsPerMeter = 0;
	BmpHeader.biYPelsPerMeter = 0;
	BmpHeader.biClrUsed = 0;
	BmpHeader.biClrImportant = 0;
	if (fwrite((void *)&BmpHeader, 1, sizeof(BmpHeader), BinFile) != sizeof(BmpHeader)) Suc = -1;
	// write Pallete
	for (i = 0, p[3] = 0; i<256; i++)
	{
		p[0] = p[1] = p[2] = i; // blue,green,red;

		if (fwrite((void *)p, 1, 4, BinFile) != 4) { Suc = -1; break; }
	}
	// write image data
	if (fwrite((void *)img, 1, width*height, BinFile) != width*height) Suc = -1;
	// return;
	fclose(BinFile);
	return Suc;
}

void Threshold(BYTE *img, int width, int height, BYTE Thre)
{
	int i;
	int size, pointer;
	BYTE LUT[256], *pBuf;

	// init LUT-look up table
	for (i = 0; i<Thre; i++) LUT[i] = 0;
	for (i = Thre; i<256; i++) LUT[i] = 255;
	// Binary image
	pBuf = img;
	size = width*height;
	for (pointer = 0; pointer<size; ++pointer)
		*(pBuf++) = LUT[*pBuf];

}