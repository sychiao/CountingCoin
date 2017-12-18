#include "func.h"

uchar* Hough(bitmap &img, int r)
{
	int index;
	uchar *copy = (uchar*)malloc(sizeof(uchar)*img.w*img.h);
	for (int i = 0; i < img.w; i++)
	{
		for (int j = 0; j < img.h; j++)
		{
			copy[i + j*img.w] = 0;
		}
	}
	for (int i = 0; i < img.w; i += 10)
	{
		for (int j = 0; j < img.h; j += 10)
		{
			index = i + j * img.w;
			if (img.pixel[index] > 0)
			{
				copy[index] = 190;
				int a = 0;
				for (int t = 0; t < 500; t++)
				{
					int x = i + r * cos(3.1415926 / 250 * t);
					int y = j + r * sin(3.1415926 / 250 * t);
					if (x >= 0 && x < img.w && y >= 0 && y < img.h)
						copy[x + y*img.w] += 30;

				}
			}
		}
	}
	return copy;
}