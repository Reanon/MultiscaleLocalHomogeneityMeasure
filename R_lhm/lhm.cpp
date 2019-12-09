#include <iostream>
#include <Windows.h>
#include "lhm.h"

void LocalHomogeneityMeasure(BYTE* img, float *buffer, int width, int height, int R, float e, BYTE* pDst)
{
	BYTE* pBuf, * p1, * p2;
	pBuf = img;
	int i, j, u, v, num, n;
	float p, q, sum, sumq;
	num = -1;
	float sigma;
	float mT,mB1,mB2,mB3,mB4,mB5,mB6,mB7,mB8;
	float d1, d2, d3, d4, d5, d6, d7, d8;
	float C, W, minD;
	//calcualte average gray value of every patch 
	for (i = 0; i <= height-R; i++)
	{
		for (int j = 0; j <= width-R; j++)
		{
			sum = 0;
			num += 1;
			for (u = 0; u < R; u++)
			{
				for (v = 0; v < R; v++)
				{
					p = *(pBuf + (i + u) * width + j + v);
					sum += p;
				}
			}
			buffer[num] = sum / (R * R); 
		}
	}
	
	for(i=(3*R-1)/2; i<height-(3*R-1)/2; i++)
	{
		for(j=(3*R-1)/2; j<width-(3*R-1)/2; j++)
		{
			u=i-(R-1)/2; v=j-(R-1)/2;
			mT = buffer[u * (width-R+1) + v];
			sumq = 0;
			for( u=i-(R-1)/2,p1=pBuf+u*width;u<=i+(R-1)/2;u++,p1+=width)
			{
				for( v=j-(R-1)/2,p2=p1+v;v<=j+(R-1)/2;v++,p2++)
				{
					p = *p2;
					q = (p - mT) * (p - mT);
					sumq += q;
				}
			}
			sigma=sqrt(sumq/(R*R));
			//calculate mBi;
			u=i+(R-1)/2+1;v=j-(R-1)/2-R;
			mB1 = buffer[u * (width-R+1) + v];
			
			u=i+(R-1)/2+1;v=j-(R-1)/2;
			mB2 = buffer[u * (width-R+1) + v];

			u=i+(R-1)/2+1;v=j+(R-1)/2+1;
			mB3 = buffer[u * (width-R+1) + v];

			u=i-(R-1)/2;v=j+(R-1)/2+1;
			mB4 = buffer[u * (width-R+1) + v];

			u=i-(R-1)/2-R;v=j+(R-1)/2+1;
			mB5 = buffer[u * (width-R+1) + v];

			u=i-(R-1)/2-R;v=j-(R-1)/2;
			mB6 = buffer[u * (width-R+1) + v];

			u=i-(R-1)/2-R;v=j-(R-1)/2-R;
			mB7 = buffer[u * (width-R+1) + v];

			u=i-(R-1)/2;v=j-(R-1)/2-R;
			mB8 = buffer[u * (width-R+1) + v];

			//calculate d`i;
			d1 = mT - mB1;
			d2 = mT - mB2;
			d3 = mT - mB3;
			d4 = mT - mB4;
			d5 = mT - mB5;
			d6 = mT - mB6;
			d7 = mT - mB7;
			d8 = mT - mB8;
			float D1, D2, D3, D4;

			if ((d1 > 0) && (d5 > 0))D1 = d1 * d5;
			else D1 = 0;

			if ((d2 > 0) && (d6 > 0))D2 = d2 * d6;
			else D2 = 0;

			if ((d3 > 0) && (d7 > 0))D3 = d3 * d7;
			else D3 = 0;

			if ((d4 > 0) && (d8 > 0))D4 = d4 * d8;
			else D4 = 0;

			float D[4] = { D1,D2,D3,D4 };
			
			minD = D[0];
			for (int k = 0; k < 4; k++)
			{
				if (D[k] < minD)
					minD = D[k];
			}
			C = minD;
			W = C * (1 / (e + sigma));
			*(pDst + i * width + j) = W;
		}
	}
}
