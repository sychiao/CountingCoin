#include "func.h"

void Otsu(bitmap &img) // Mat hist
{
	// memcpy(oldimg.pixel, img.pixel, (std::size_t) sizeof(uchar)*img.w * img.h ); // memory copying. 從img.pixel陣列複製長度為sizeof(uchar)*img.w * img.h(整張圖片長乘寬的數值)
	uchar* dst = img.pixel;
	
	float min = OtsuPart(img.pixel, 0);
	
	int index=0;
	int minindex = 256;
	//printf("min:%f", min);
	// 先改出C版本，再改成CUDA，
	// 格式統一
	
	for (int i = 0; i < img.w; i++) // i: row index
	{
		for (int j = 0; j < img.h; j++) // j: column index
		{
			dst[i + j*img.w] = 0; // initialization of dst[]
			
			float val = OtsuPart(img.pixel, i + j*img.w);
			printf("val:%f\n", val);
			if (val - min < 0)
			{
				min = val;
				minindex = i + j*img.w;
			}
		}
	}	
	//return minindex; // 目的，找最小值
}

float OtsuPart(uchar *dst, g, int *p, int fw, int fh) // (Mat hist)
{
	float avg1 = 1, avg2 = 1; // average1, average2
	int s1 = 0, s2 = 0; 
	
	for (int i = 0; i < img.w; i++) // i: row index
	{
		for (int j = 0; j < img.h; j++) // j: column index
		{
			int val = cvRound(dst.at<uchar>(i + j*img.h)); // 改成自己的版本	，給個數字可以知道像素，準備256*256
			if ( (i + j*img.h) < t)
			{
				s1 += (i + j*img.h)*val;
				avg1 += val;
			}
			else
			{
				s2 += (i + j*img.h)*val;
				avg2 += val;
			}
		}
	}
	
	float u1=0, u2=0;
	u1 = s1 / avg1;
	u2 = s2 / avg2;
	float sigma1 = 0, sigma2 = 0;
	
	for (int i = 0; i < img.w; i++) // i: row index
	{
		for (int j = 0; j < img.h; j++) // j: column index
		{
			int val = cvRound(dst.at<uchar>(i + j*img.h));
			if ( (i + j*img.h) < t)
			{
				sigma1 += (u1 - (i + j*img.h))*(u1 - (i + j*img.h))*val;
			}
			else
			{
				sigma2 += (u2 - (i + j*img.h))*(u2 - (i + j*img.h))*val;
			}
		}
	}
	
	return sigma1 + sigma2; // 
}