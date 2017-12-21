#include <iostream>
#include <vector>
#include "func.h"

using namespace cv;

void drawCircle(Mat &input, const std::vector<Vec3f> &circles)
{
    for(int i=0; i<circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle(input, center, radius, Scalar(255,0,0), 3, 8, 0 );
    }
}

int main()
{
    struct timeval tv0, tv;
    gettimeofday(&tv0,NULL);
        gettimeofday(&tv,NULL);
        TimeDiff(tv0,tv);

    char* I = "coincoin.png";
    Mat srcImg = imread(I,CV_LOAD_IMAGE_GRAYSCALE);
    Mat result = imread(I);
    Mat dst;
    threshold(srcImg, dst, 190, 255, THRESH_BINARY|THRESH_OTSU);
    //imshow("fuck",dst);
    Mat dst2;
    Mat mask1 = getStructuringElement(MORPH_RECT,Size(6,6));
        gettimeofday(&tv,NULL);
        TimeDiff(tv0,tv);
    erode(dst,dst2,mask1);
        gettimeofday(&tv,NULL);
        TimeDiff(tv0,tv);
    dilate(dst2,dst,mask1);
        gettimeofday(&tv,NULL);
        TimeDiff(tv0,tv);
    Canny(dst,dst,3,9,3);
        gettimeofday(&tv,NULL);
        TimeDiff(tv0,tv);
    std::vector<Vec3f> circles;
    HoughCircles(dst, circles, CV_HOUGH_GRADIENT, 2, 50, 100, 100);
        gettimeofday(&tv,NULL);
        TimeDiff(tv0,tv);
    std::cout<<"Hello:"<<circles.size();
    drawCircle(result,circles);
    //namedWindow("hello world");
    //imshow("hello world",result);
//    waitKey(0);
    return 0;
}
