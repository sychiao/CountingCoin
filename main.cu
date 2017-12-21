#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include "func.h"
#include "func.cuh"

using namespace cv;

// global tmp memory
//__device__ int d_tmp[10];

int main()
{
    struct timeval tv0, tv;
    gettimeofday(&tv0,NULL);
        gettimeofday(&tv,NULL);
        TimeDiff(tv0,tv);


	Mat srcImg = imread("coincoin.png", CV_LOAD_IMAGE_GRAYSCALE);


// Prepare global tmp mem
//    uchar** tmp;
//    cudaError err;
//    size_t s;
//    err = cudaGetSymbolSize ( &s, "d_tmp"
//            )   ;
    //err = cudaGetSymbolAddress((void**)&tmp,"d_tmp");
//    CHECK_ERROR(err);

	threshold(srcImg, srcImg, 190, 255, THRESH_BINARY | THRESH_OTSU);
	Mat mask1 = getStructuringElement(MORPH_RECT, Size(6, 6));

    Mat n = srcImg.clone();
	bitmap img(srcImg);
    bitmap oldimg(img);

    uchar* tmp1;
    uchar* tmp2;
    uchar* d_img_pixel;
    uchar* d_oldimg_pixel;
    cudaMalloc(&d_img_pixel, sizeof(uchar) * img.w * img.h);
    cudaMalloc(&d_oldimg_pixel, sizeof(uchar) * img.w * img.h);

    /************ 8 Line *****************************/
    cudaMemcpy(d_img_pixel, img.pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyHostToDevice);
    cudaMemcpy(d_oldimg_pixel, oldimg.pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyHostToDevice);
    tmp1 = img.pixel;
    tmp2 = oldimg.pixel;
    img.pixel = d_img_pixel;
    oldimg.pixel = d_oldimg_pixel;
    /****************************************/

        gettimeofday(&tv,NULL);
        TimeDiff(tv0,tv);
	Erode(img);
        gettimeofday(&tv,NULL);
        TimeDiff(tv0,tv);
	Dilate(img);


    /********* 5 Linw img show ***************/
//    cudaMemcpy(tmp1, img.pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyDeviceToHost);
//    n.data = tmp1;
//	imshow("Tmp", n);
    /***********************************/

        gettimeofday(&tv,NULL);
        TimeDiff(tv0,tv);
	Sobel(img);

    oldimg.pixel = (uchar*)malloc(sizeof(uchar)*img.w*img.h);

   // for(int r=50;r<150;r+=2)
        gettimeofday(&tv,NULL);
        TimeDiff(tv0,tv);
    Hough(img, oldimg, 113);
        gettimeofday(&tv,NULL);
        TimeDiff(tv0,tv);

    /************ 8 Line *****************************/
    cudaMemcpy(tmp1, img.pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyDeviceToHost);
    cudaMemcpy(tmp2, oldimg.pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyDeviceToHost);
    img.pixel = tmp1;
    oldimg.pixel = tmp2;
    /****************************************/

	Mat m2 = Mat(img.h, img.w, CV_8UC1);
	memcpy(m2.data, img.pixel, img.w*img.h * sizeof(uchar));
//	imshow("After hough", m2);
	GaussianBlur(m2, m2, Size(9, 9), 0, 0);
	threshold(m2, m2, 30, 255, THRESH_BINARY );

	//imshow("Final", m2);
	//waitKey(0);
	return 0;
}
