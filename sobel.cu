
#include "func.h"
#define N 512



__global__
void Convolution(uchar *f, int *p, int fw, int fh, int a0b1bu2, int gw, int gh)
{
    // Share
    int a[] = { 1,0,-1,
                2,0,-2,
                1,0,-1 };
    int b[] = { 1,2,1,
                0,0,0,
               -1,-2,-1 };
	int bu[] = { 1,1,1,1,1,
		1,2,5,2,1,
		1,5,11,5,1,
		1,2,5,2,1,
		1,1,1,1,1 };
    int* select[] = {a,b,bu};
    int* g = select[a0b1bu2];
	if (gw % 2 * gh % 2 == 0)
	{
        // Error
        asm("trap;");
		return;
	}
    int index = blockIdx.x *blockDim.x + threadIdx.x;
    if ( index >= fh*fw ) {
        return;
    }

    int i = index % fw;
    int j = index / fw;

    int val = 0;
    for (int k = 0; k < gw; k++)
    {
        for (int l = 0; l < gh; l++)
        {
            if (i - gw / 2 < 0 || j - gh / 2 < 0)
            {
                val += 0;
            }
            else
            {
                val += f[(i - gw / 2 + k) + (j - gh / 2 + l)*fw] * g[k + l*gw];
            }
        }
    }
    p[i + j*fw] = val;
}

__global__
void copy_back(uchar* dst, int* src, int h, int w)
{
    int index = blockIdx.x *blockDim.x + threadIdx.x;
    if ( index < h*w ) {
	    dst[index] = src[index] / 55;
    }
}


__global__
void compute(uchar* pixel, int* gx, int* gy, int w, int h)
{
    int index = blockIdx.x *blockDim.x + threadIdx.x;
    if ( index >= h*w ) {
        return;
    }

    int i = index % w;
    int j = index / w;

    float G = sqrt((float)gx[index] * gx[index] + gy[index] * gy[index]);
    float theta;
    if (G > 75 && gx[index] != 0)
        theta = atan((float) gy[i + j*h] / gx[index]);
    else
        theta = 3.1415926 / 2;
    float dir = theta / (2 * 3.1415926);
    float value = 0;
    int x = 0, y = 0;
    if (dir< (1. / 8.) || dir>(7. / 8.))
        x = 1;
    else if (dir < (3. / 8.))
        y = -1;
    else if (dir < (5. / 8.))
        x = -1;
    else
        y = 1;
    index = (i + x) + (j + y)*w;
    if ((i + x) < w && (j + y) < h && (i + x)>0 && (j + y) >0)
    {
        if (sqrt((float) gx[index] * gx[index] + gy[index] * gy[index]) < G)
            value = G;
    }
    if (value > 75)
        pixel[i + j*w] = 255;
    else
        pixel[i + j*w] = 0;
}

void Sobel(bitmap &img)
{
/*
	int *bur = (int*)malloc(sizeof(int)*img.w*img.h);
	int *gx = (int*)malloc(sizeof(int)*img.w*img.h);
	int *gy = (int*)malloc(sizeof(int)*img.w*img.h);
*/
	int *bur;
	int *gx;
	int *gy;
    uchar* pixel;

// Not support full cuda
//*
    
    cudaMalloc(&pixel, sizeof(int)*img.w*img.h);
    cudaMemcpy(pixel, img.pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyHostToDevice);
//*/

    cudaMalloc(&bur, sizeof(int)*img.w*img.h);
    cudaMalloc(&gx, sizeof(int)*img.w*img.h);
    cudaMalloc(&gy, sizeof(int)*img.w*img.h);

    Convolution<<<(img.w * img.h + N) / N, N>>>(pixel, bur, img.w, img.h, 2, 5, 5);

    // Kernel 1
    copy_back<<<(img.w * img.h + N) / N, N>>>(pixel, bur, img.h, img.w);

	Convolution<<<(img.w * img.h + N) / N, N>>>(pixel, gx, img.w, img.h, 0, 3, 3);
	Convolution<<<(img.w * img.h + N) / N, N>>>(pixel, gy, img.w, img.h, 1, 3, 3);

    // Kernel 2
    compute<<<(img.w * img.h + N) / N, N>>>(pixel, gx, gy, img.w, img.h);

    cudaMemcpy(img.pixel, pixel, sizeof(uchar)*img.w*img.h, cudaMemcpyDeviceToHost);

    cudaFree(bur);
    cudaFree(gx);
    cudaFree(gy);
    cudaFree(pixel);
}
