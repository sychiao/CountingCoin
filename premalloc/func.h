#ifndef __FUNC_H
#define __FUNC_H

#include<sys/time.h>
#include<stdio.h>
#include <opencv2/opencv.hpp>

#define BLOCK_SIZE 512

#define CHECK_ERROR( err ) \
      if( err != cudaSuccess ) { \
              std::cerr << "File: " << __FILE__  << " Line " << __LINE__ << " ERROR: " << cudaGetErrorString( err ) << std::endl; \
              exit( -1 ); \
            }

#define CHECK_LAST_ERROR \
      { cudaError_t err = cudaGetLastError(); \
              if( err != cudaSuccess ) { \
                        std::cerr << "File: " << __FILE__ <<  " Line " << __LINE__ << cudaGetErrorString( err ) << std::endl; \
                        exit( -1 ); \
                      } \
            }  

class bitmap
{
public:
	int w;
	int h;
	uchar *pixel;
	bitmap(cv::Mat mat)
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


void Erode(bitmap &img, uchar* &d_buffer);
void Dilate(bitmap &img, uchar* &d_buffer);
void Sobel(bitmap &img, uchar* &d_buffer);
void Hough(bitmap &img, bitmap &oldimg, int r, uchar* &d_buffer);
void Otsu(bitmap &img);

void TimeDiff(struct  timeval* start, struct  timeval* end);

#endif
