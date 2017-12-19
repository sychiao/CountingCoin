#include "func.h"


__global__
void Zero(uchar* dst, int h, int w)
{
    int index = blockIdx.x *blockDim.x + threadIdx.x;
	if ( index >= h*w ) {
        return;
    }
	dst[index] = 0;
}

__global__
void Hough_compute(uchar* img, uchar* oldimg, int h, int w, int r)
{
    int index = blockIdx.x *blockDim.x + threadIdx.x;
    uchar* dst = img;
	if ( index >= h*w ) {
        return;
    }
	int i = index % w;
    int j = index / w;

#define ONE_STEP 10

	if ((oldimg[index] > 0) && (i % ONE_STEP == 0) && (j % ONE_STEP == 0) ) {
		dst[index] = 190;
		//int a = 0;
        int x, y;
		for (int t = 0; t < 500; t++)
		{
			x = i + r * cos(3.1415926 / 250 * t);
			y = j + r * sin(3.1415926 / 250 * t);
			if (x >= 0 && x < w && y >= 0 && y < h) {
				atomicAdd((int*)&dst[x + y * w], 30);
            }
		}
	}
}
void Hough(bitmap &img, bitmap &oldimg, int r)
{
    cudaError err;
//* Not support full cuda
    uchar* pixel;
    uchar* oldpixel;

    err = cudaMalloc(&pixel, sizeof(uchar)*img.w*img.h);
    CHECK_ERROR( err)
    err = cudaMalloc(&oldpixel, sizeof(uchar)*img.w*img.h);
    CHECK_ERROR( err)

    err= cudaMemcpy(pixel, img.pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyHostToDevice);
    CHECK_ERROR( err)
    //cudaMemcpy(oldpixel, oldimg.pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyHostToDevice);
//*/

    //memcpy( oldimg.pixel, img.pixel, (std::size_t) sizeof(uchar)*img.w * img.h );
    err= cudaMemcpy(oldpixel, pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyDeviceToDevice);
    CHECK_ERROR( err)

    Zero<<<(img.w * img.h + BLOCK_SIZE) / BLOCK_SIZE, BLOCK_SIZE>>>(pixel, img.h, img.w);
    CHECK_LAST_ERROR
	Hough_compute<<<(img.w * img.h + BLOCK_SIZE) / BLOCK_SIZE, BLOCK_SIZE>>>(pixel, oldpixel, img.h, img.w, r);
    CHECK_LAST_ERROR
//*

    err= cudaMemcpy(img.pixel, pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyDeviceToHost);
    CHECK_ERROR( err)
    err= cudaMemcpy(oldimg.pixel, oldpixel, sizeof(uchar)*img.w*img.h, cudaMemcpyDeviceToHost);
    CHECK_ERROR( err)
    err= cudaFree(pixel);
    CHECK_ERROR( err)
    err= cudaFree(oldpixel);
    CHECK_ERROR( err)

//*/
}
