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
	erode(srcImg, srcImg, mask1, Point(-1, -1), 1);
	dilate(srcImg, srcImg, mask1, Point(-1, -1), 1);
	
	Mat n = srcImg.clone();
	imshow("Hell2", n);
	bitmap img(srcImg);
	
	Sobel(img);
	uchar *p = Hough(img,113);
	
	Mat m = Mat(img.h, img.w, CV_8UC1);
	memcpy(m.data, img.pixel, img.w*img.h*sizeof(uchar));
	Mat m2 = Mat(img.h, img.w, CV_8UC1);
	memcpy(m2.data, p, img.w*img.h * sizeof(uchar));
	GaussianBlur(m2, m2, Size(9, 9), 0, 0);
	threshold(m2, m2, 50, 255, THRESH_BINARY );
	
	Mat m3 = m2.clone();
	bitmap cool(m3);
	uchar *pp = Hough(cool,115);

	Mat m4 = Mat(img.h, img.w, CV_8UC1);
	memcpy(m4.data, pp, img.w*img.h * sizeof(uchar));

	//imshow("Hello",m4);
	imshow("Hello22", m2);
	waitKey(0);
	return 0;
}
