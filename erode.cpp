#include "func.h"
/**int getindex(int x, int y)
{
	if (x > w || y > h || x < 0 || y<0)
		return 0;
	return x + y*w;
}*/

#define getindex( x,y) ( x) + ( y) * img.w

void Dilate(bitmap &img)
{
	uchar *ptr = (uchar*)malloc(sizeof(uchar)*img.w*img.h);
	memcpy(ptr, img.pixel, sizeof(uchar)*img.h*img.w);
	for (int i = 3; i < img.w-3; i++)
	{
		for (int j = 3; j < img.h-3; j++)
		{
			int start = 0;
            int index = i + j * img.w;
			for (int k = -3; k <= 3; k++)
			{
				for (int l = -3; l <= 3; l++)
				{
					if (img.pixel[getindex(i + k, j + l)] == 255)
					{
						ptr[index] = 255;
						start = 1;
						break;
					}
					
				}
				if (start == 1)
					break;
			}
			if(start == 0)
				ptr[index] = 0;
		}
	}
//	memcpy(img.pixel, ptr, sizeof(uchar)*img.h*img.w);
    free(img.pixel);
    img.pixel = ptr;
}

void Erode(bitmap &img)
{
	uchar *ptr = (uchar*)malloc(sizeof(uchar)*img.w*img.h);
	memcpy(ptr, img.pixel, sizeof(uchar)*img.h*img.w);	
	for (int i = 3; i < img.w - 3; i++)
	{
		for (int j = 3; j < img.h - 3; j++)
		{
			int start = 0;
            int index = i + j * img.w;
			for (int k = -3; k <= 3; k++)
			{
				for (int l = -3; l <= 3; l++)
				{
					if (img.pixel[getindex(i + k, j + l)] != 255)
					{
						ptr[index] = 0;
						start = 1;
						break;
					}
				}
				if (start == 1)
					break;
			}
			if (start == 0)
				ptr[index] = 255;
				
		}
	}
	//memcpy(img.pixel, ptr, sizeof(uchar)*img.h*img.w);	
    free(img.pixel);
    img.pixel = ptr;
}
