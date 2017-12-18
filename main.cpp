#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

class bitmap
{
public:
	int w;
	int h;
	uchar *pixel;
	bitmap(Mat mat);
};

bitmap::bitmap(Mat mat)
{
	w = mat.cols;
	h = mat.rows;
	pixel = (uchar*)malloc(sizeof(uchar)*w*h);
	if (mat.isContinuous())
		pixel = mat.data;
	else
		printf("not continuous");
}

int main()
{
	Mat srcImg = imread("coin.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	bitmap img(srcImg);
	
	waitKey(0);
	return 0;
}
