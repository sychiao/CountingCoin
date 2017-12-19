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
        if (mat.isContinuous()) {
            memcpy( pixel, mat.data, (std::size_t) sizeof(uchar)*w*h );
        } else {
            printf("not continuous");
        }
    }
	bitmap(const bitmap& img)
    {
        w = img.w;
        h = img.h;
        pixel = (uchar*)malloc(sizeof(uchar)*w*h);
    }
};


void Sobel(bitmap &img);
void Hough(bitmap &img, bitmap &oldimg, int r);

#endif
