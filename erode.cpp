#include "func.h"
int getindex(int x, int y, int w, int h)
{
	if (x > w || y > h || x < 0 || y<0)
		return 0;
	return x + y*w;
}

void Erode(bitmap &img)
{
	uchar *ptr = (uchar*)malloc(sizeof(uchar)*img.w*img.h);
	for (int i = 0; i < img.w; i++)
	{
		for (int j = 0; j < img.h; j++)
		{
			int start = 0;
			for (int k = -3; k <= 3; k++)
			{
				for (int l = -3; l <= 3; l++)
				{
					int index = getindex(i + k, j + l, img.w, img.h);
					if (img.pixel[index] == 255)
					{
						ptr[getindex(i, j, img.w, img.h)] = 255;
						start = 1;
						break;
					}
					
				}
				if (start == 1)
					break;
			}
			if(start == 0)
				ptr[getindex(i, j, img.w, img.h)] = 0;
		}
	}
	memcpy(img.pixel, ptr, sizeof(uchar)*img.h*img.w);
}

void dila(bitmap &img)
{
	uchar *ptr = (uchar*)malloc(sizeof(uchar)*img.w*img.h);
	for (int i = 0; i < img.w; i++)
	{
		for (int j = 0; j < img.h; j++)
		{
			int start = 0;
			for (int k = -3; k <= 3; k++)
			{
				for (int l = -3; l <= 3; l++)
				{
					if (img.pixel[getindex(i + k, j + l, img.w, img.h)] != 255)
					{	
						ptr[getindex(i, j, img.w, img.h)] = 0;
						start = 1;
						break;
					}
				}
				if (start == 1)
					break;
			}
			if (start == 0)
				ptr[getindex(i, j, img.w, img.h)] = 255;
				
		}
	}
	memcpy(img.pixel, ptr, sizeof(uchar)*img.h*img.w);	
}