#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include "func.h"

using namespace cv;

int main()
{
	Mat srcImg = imread("coincoin.png", CV_LOAD_IMAGE_GRAYSCALE);
	threshold(srcImg, srcImg, 190, 255, THRESH_BINARY | THRESH_OTSU);
	Mat mask1 = getStructuringElement(MORPH_RECT, Size(6, 6));

    Mat n = srcImg.clone();
	bitmap img(srcImg);
	//erode(srcImg, srcImg, mask1, Point(-1, -1), 1);
	//dilate(srcImg, srcImg, mask1, Point(-1, -1), 1);
	Erode(img);
	Dilate(img);
	Erode(img);
	Dilate(img);
	Dilate(img);
    n.data = img.pixel;
	
	imshow("Hell2", n);
	
	Sobel(img);

	bitmap oldimg(img);
    oldimg.pixel = (uchar*)malloc(sizeof(uchar)*img.w*img.h);

/*
	Mat m = Mat(img.h, img.w, CV_8UC1);
	memcpy(m.data, img.pixel, img.w*img.h*sizeof(uchar));
    imshow("Hello22", m);
	waitKey(0);
	return 0;
*/
   // for(int r=50;r<150;r+=2)
    Hough(img, oldimg, 113);

	Mat m2 = Mat(img.h, img.w, CV_8UC1);
	memcpy(m2.data, img.pixel, img.w*img.h * sizeof(uchar));
//	imshow("After hough", m2);
	GaussianBlur(m2, m2, Size(9, 9), 0, 0);
	threshold(m2, m2, 30, 255, THRESH_BINARY );

	imshow("Final", m2);
	waitKey(0);
	return 0;
}