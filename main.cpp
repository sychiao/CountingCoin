#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <string>

#include "header.h"

using namespace cv;

void print_Mat_type(Mat M) {
  int type = M.type();
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  printf("Matrix: %s %dx%d \n", r.c_str(), M.cols, M.rows );
}

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
    Mat srcImg = imread("coin.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    Mat result = imread("coin.jpg");
    Mat dst;

    // C type image
    unsigned char** image;
    unsigned char** tmp_image;


    // Get image size
    int rows = result.rows;
    int cols = result.cols;

//    printf("Image row: %d ,col: %d\n", rows, cols);

    threshold(srcImg, dst, 190, 255, THRESH_BINARY|THRESH_OTSU);
    imshow("fuck",dst);
    Mat tmp;
    Mat mask1 = getStructuringElement(MORPH_RECT,Size(6,6));
    erode(dst,tmp,mask1);
    dilate(tmp,dst,mask1);

    Mat test= dst.clone(); 

    print_Mat_type(dst);
    image = new unsigned char*[rows];
    tmp_image = new unsigned char*[cols];


    for (int i=0; i < rows; ++i) {
        image[i] = new uchar[cols];
        tmp_image[i] = new uchar[cols];
        image[i] = dst.ptr<uchar>(i);
        tmp_image[i] = tmp.ptr<uchar>(i);
    }
    sobel_filtering(image, tmp_image, cols, rows);

    Canny(test,test,3,9,3);

    imshow("CV ",test);
//    imshow("hello world",dst);
    imshow("hello world2",tmp);
    std::vector<Vec3f> circles;
    HoughCircles(test, circles, CV_HOUGH_GRADIENT, 2, 50, 100, 100);

    for (Vec3f vec : circles)
            std::cout << vec.val[0] << std::endl;


    std::cout<<"Hello:"<<circles.size();
/*    drawCircle(result,circles);
    namedWindow("hello world");
    imshow("hello world",result);*/
    waitKey(0);
    return 0;
}
