#pragma once
#ifndef _LHM_H_
#define _LHM_H_
//typedef unsigned char BYTE;
void LocalHomogeneityMeasure(
	BYTE* img,       //input image
	float* buffer,
	int width,
	int height,
	int R,           //length of every patch
	float e,         //prior parameter
	BYTE* pDst);      //output image
#endif // !1

