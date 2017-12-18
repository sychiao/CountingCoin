
#include "func.h"

static void Convolution(uchar *f, int *p, int fw, int fh, int *g, int gw, int gh)
{
	if (gw % 2 * gh % 2 == 0)
	{
        // Error
		return;
	}

	for (int i = 0; i < fw; i++)
	{
		for (int j = 0; j < fh; j++)
		{
			int val = 0;
			for (int k = 0; k < gw; k++)
			{
				for (int l = 0; l < gh; l++)
				{
					if (i - gw / 2 < 0 || j - gh / 2 < 0)
					{
						val += 0;
					}
					else
					{
						val += f[(i - gw / 2 + k) + (j - gh / 2 + l)*fw] * g[k + l*gw];
					}
				}
			}
			p[i + j*fw] = val;
		}
	}
}
void Sobel(bitmap &img)
{
	int a[] = { 1,0,-1,
		2,0,-2,
		1,0,-1 };
	int b[] = { 1,2,1,
		0,0,0,
		-1,-2,-1 };
	int bu[] = { 1,1,1,1,1,
		1,2,5,2,1,
		1,5,11,5,1,
		1,2,5,2,1,
		1,1,1,1,1 };

	int *bur = (int*)malloc(sizeof(int)*img.w*img.h);
    Convolution(img.pixel, bur, img.w, img.h, bu, 5, 5);

	for (int i = 0; i < img.w; i++)
	{
		for (int j = 0; j < img.h; j++)
		{
			img.pixel[i + j*img.h] = bur[i + j*img.h] / 55;
		}
	}

	int *gx = (int*)malloc(sizeof(int)*img.w*img.h);
	int *gy = (int*)malloc(sizeof(int)*img.w*img.h);

	Convolution(img.pixel, gx, img.w, img.h, a, 3, 3);
	Convolution(img.pixel, gy, img.w, img.h, b, 3, 3);

	for (int i = 0; i < img.w; i++)
	{
		for (int j = 0; j < img.h; j++)
		{
			int index = i + j*img.w;
			float G = sqrt(gx[index] * gx[index] + gy[index] * gy[index]);
			float theta;
			if (G > 75 && gx[index] != 0)
				theta = atan(gy[i + j*img.h] / gx[index]);
			else
				theta = 3.1415926 / 2;
			float dir = theta / (2 * 3.1415926);
			float value = 0;
			int x = 0, y = 0;
			if (dir< (1. / 8.) || dir>(7. / 8.))
				x = 1;
			else if (dir < (3. / 8.))
				y = -1;
			else if (dir < (5. / 8.))
				x = -1;
			else
				y = 1;
			index = (i + x) + (j + y)*img.w;
			if ((i + x) < img.w && (j + y) < img.h && (i + x)>0 && (j + y) >0)
			{
				if (sqrt(gx[index] * gx[index] + gy[index] * gy[index]) < G)
					value = G;
			}
			if (value > 75)
				img.pixel[i + j*img.w] = 255;
			else
				img.pixel[i + j*img.w] = 0;
		}
	}
}
