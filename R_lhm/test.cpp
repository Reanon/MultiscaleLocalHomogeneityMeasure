#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <time.h>
#include "bmp.h"
#include "lhm.h"

int main()
{
	BYTE* srcImg, * dstImg;
	int width, height;
	float* buffer;
	buffer = new float[500 * 500];
	char infile[100], outfile[100];
	for(int k=0; k<100; k++)
	{
		sprintf(infile, "D:\\Documents\\CppProject\\BmpImage_Data\\lihong_data_8\\%05d.bmp", k);
		srcImg = Read8BitBmpFile2Img(infile, &width, &height);
		dstImg = new BYTE[width * height * sizeof(BYTE)];
		clock_t startTime, endTime;
	    startTime = clock();//计时开始
		LocalHomogeneityMeasure(srcImg, buffer, width, height, 3, 0.001, dstImg);
		endTime = clock();//计时结束
	    std::cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
		sprintf(outfile, "D:\\Desktop\\test\\%05d.bmp", k);
		Write8BitImg2BmpFile(dstImg, width, height, outfile);
		delete[]srcImg;
		delete[]dstImg;
	}
	/*srcImg = YwkRead8BitBmpFile2Img("F:\\data\\00005.bmp", &width, &height);
	dstImg = new BYTE[width * height * sizeof(BYTE)];
	clock_t startTime, endTime;
	startTime = clock();
	for(int k=0;k<100;k++)
	Lh_lhm(srcImg, width, height, 3, 0.001, dstImg);
	endTime = clock();
	std::cout << "The Running Time is:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
	YwkWrite8BitImg2BmpFile(dstImg, width, height, "F:\\R.bmp");

	delete[]srcImg;
	delete[]dstImg;*/
	system("pause");
}