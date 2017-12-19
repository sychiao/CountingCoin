#ifndef __FUNC_H
#define __FUNC_H
#include <opencv2/opencv.hpp>
using namespace cv;
class bitmap
{
public:
	int w;
	int h;
	uchar *pixel;
	bitmap(Mat mat)
    {
        w = mat.cols;
        h = mat.rows;
        pixel = (uchar*)malloc(sizeof(uchar)*w*h);
        if (mat.isContinuous())
            pixel = mat.data;
        else
            printf("not continuous");
    }
};


void Sobel(bitmap &img);
uchar* Hough(bitmap &img, int r);

#endif
