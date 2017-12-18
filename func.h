#include <opencv2\opencv.hpp>
using namespace cv;
class bitmap
{
public:
	int w;
	int h;
	uchar *pixel;
	bitmap(Mat mat);
};
void Sobel(bitmap &img);
int* Convolution(uchar *f, int fw, int fh, int *g, int gw, int gh);
