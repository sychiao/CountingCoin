#include "func.h"
/**int getindex(int x, int y)
{
	if (x > w || y > h || x < 0 || y<0)
		return 0;
	return x + y*w;
}*/

#define getindex( x,y) ( x) + ( y) * w

__global__
void Dilate_compute(uchar* dst, uchar* src, int h, int w)
{
    int index = blockIdx.x *blockDim.x + threadIdx.x;
    int i = index % w;
    int j = index / w;

    if ( index >= h * w ) {
        return;
    }

	if ( i <= 3 && i >= w-3 && j <= 3 && j >= h-3 )
	{
        dst[index] = src[index];
        return;
    }

    int start = 0;
    for (int k = -3; k <= 3; k++)
    {
        for (int l = -3; l <= 3; l++)
        {
            if (src[getindex(i + k, j + l)] == 255)
            {
                dst[index] = 255;
                start = 1;
                break;
            }
        }
        if (start == 1)
            break;
    }
    if(start == 0)
        dst[index] = 0;
}

void Dilate(bitmap &img)
{
    uchar* pixel = img.pixel;
    uchar* ptr;

    cudaMalloc(&ptr, sizeof(uchar)*img.w*img.h);
//    cudaMemcpy(ptr, pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyDeviceToDevice);


	//uchar *ptr = (uchar*)malloc(sizeof(uchar)*img.w*img.h);
	//memcpy(ptr, img.pixel, sizeof(uchar)*img.h*img.w);

    Dilate_compute<<<(img.w * img.h + BLOCK_SIZE) / BLOCK_SIZE, BLOCK_SIZE>>>(ptr, pixel, img.h, img.w);

    img.pixel = ptr;
    ptr = pixel;
    cudaFree(ptr);
}


__global__
void Erode_compute(uchar* dst, uchar* src, int h, int w)
{
    int index = blockIdx.x *blockDim.x + threadIdx.x;
    int i = index % w;
    int j = index / w;

    if ( index >= h * w ) {
        return;
    }

	if ( i <= 3 && i >= w-3 && j <= 3 && j >= h-3 )
	{
        dst[index] = src[index];
        return;
    }


    int start = 0;
    for (int k = -3; k <= 3; k++)
    {
        for (int l = -3; l <= 3; l++)
        {
            if (src[getindex(i + k, j + l)] != 255)
            {
                dst[index] = 0;
                start = 1;
                break;
            }
        }
        if (start == 1)
            break;
    }
    if (start == 0)
        dst[index] = 255;

}


void Erode(bitmap &img)
{
    uchar* pixel = img.pixel;
    uchar* ptr;

    cudaMalloc(&ptr, sizeof(uchar)*img.w*img.h);
//    cudaMemcpy(ptr, pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyDeviceToDevice);

    Erode_compute<<<(img.w * img.h + BLOCK_SIZE) / BLOCK_SIZE, BLOCK_SIZE>>>(ptr, pixel, img.h, img.w);

    img.pixel = ptr;
    ptr = pixel;
    cudaFree(ptr);
}
