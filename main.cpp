#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include "func.h"

using namespace cv;

int main()
{
    struct timeval tv0, tv;
    gettimeofday(&tv0,NULL);
	Mat srcImg = imread("coincoin.png", CV_LOAD_IMAGE_GRAYSCALE);
	threshold(srcImg, srcImg, 190, 255, THRESH_BINARY | THRESH_OTSU);
	Mat mask1 = getStructuringElement(MORPH_RECT, Size(6, 6));

    Mat n = srcImg.clone();
	bitmap img(srcImg);

        TimeDiff(&tv0,&tv);
	Erode(img);
        TimeDiff(&tv0,&tv);
	Dilate(img);
        TimeDiff(&tv0,&tv);

    n.data = img.pixel;
	//imshow("Hell2", n);

	Sobel(img);
        TimeDiff(&tv0,&tv);

	bitmap oldimg(img);
    oldimg.pixel = (uchar*)malloc(sizeof(uchar)*img.w*img.h);

    Hough(img, oldimg, 113);
        TimeDiff(&tv0,&tv);

	Mat m2 = Mat(img.h, img.w, CV_8UC1);
	memcpy(m2.data, img.pixel, img.w*img.h * sizeof(uchar));
	GaussianBlur(m2, m2, Size(9, 9), 0, 0);
	threshold(m2, m2, 30, 255, THRESH_BINARY );

	//imshow("Final", m2);
	//waitKey(0);
	return 0;
}
