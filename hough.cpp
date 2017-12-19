#include "func.h"

void Hough(bitmap &img, bitmap &oldimg, int r)
{

    memcpy( oldimg.pixel, img.pixel, (std::size_t) sizeof(uchar)*img.w * img.h );
    uchar* dst = img.pixel;
	int index;
	for (int i = 0; i < img.w; i++)
	{
		for (int j = 0; j < img.h; j++)
		{
			dst[i + j*img.w] = 0;
		}
	}
	for (int i = 0; i < img.w; i += 10)
	{
		for (int j = 0; j < img.h; j += 10)
		{
			index = i + j * img.w;
			if (oldimg.pixel[index] > 0)
			{
				dst[index] = 190;
				int a = 0;
				for (int t = 0; t < 500; t++)
				{
					int x = i + r * cos(3.1415926 / 250 * t);
					int y = j + r * sin(3.1415926 / 250 * t);
					if (x >= 0 && x < img.w && y >= 0 && y < img.h)
						dst[x + y*img.w] += 30;

				}
			}
		}
	}
}
