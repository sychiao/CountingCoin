#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include "func.h"

using namespace cv;

void Hough(bitmap &img)
{
	int index;
	for (int i = 0; i < img.w; i++)
	{
		for (int j = 0; j < img.h; j++)
		{
			index = i + j * img.w;

		}
	}
}

int main()
{
	Mat srcImg = imread("coincoin.png", CV_LOAD_IMAGE_GRAYSCALE);
	threshold(srcImg, srcImg, 190, 255, THRESH_BINARY | THRESH_OTSU);
	Mat mask1 = getStructuringElement(MORPH_RECT, Size(6, 6));
	erode(srcImg, srcImg, mask1, Point(-1, -1), 1);
	dilate(srcImg, srcImg, mask1, Point(-1, -1), 1);
	
	Mat n = srcImg.clone();
	imshow("Hell2", n);
	bitmap img(srcImg);
	
	Sobel(img);

	Mat m = Mat(img.h, img.w, CV_8UC1);
	memcpy(m.data, img.pixel, img.w*img.h*sizeof(uchar));

	imshow("Hello",m);
	waitKey(0);
	return 0;
}
