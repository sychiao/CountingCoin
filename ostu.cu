#include "func.h" // load image 格式
#include "func.cuh" // load image 格式
// image格式統一, 一維

__global__
void Zero(int* dst, int h, int w)
{
    int index = blockIdx.x *blockDim.x + threadIdx.x;
	if ( index >= h*w ) {
        return;
    }
	dst[index] = 0;
}

__global__ float OtsuPart(uchar *dst, g, int *p, int fw, int fh) // (Mat hist)
{
	float avg1 = 1, avg2 = 1; // average1, average2
	int s1 = 0, s2 = 0; 
	
	int index = blockIdx.x *blockDim.x + threadIdx.x;
	if(index>=fh*fw){
		return;
	}
	
	int i = index % fw;
    int j = index / fw;
	
	for (int i = 0; i < img.w; i++) // i: row index
	{
		for (int j = 0; j < img.h; j++) // j: column index
		{
			int val = cvRound(dst.at<uchar>(i + j*img.h)); // 改成自己的版本	，給個數字可以知道像素，準備256*256
			if ( (i + j*img.h) < t)
			{
				s1 += (i + j*img.h)*val;
				avg1 += val;
			}
			else
			{
				s2 += (i + j*img.h)*val;
				avg2 += val;
			}
		}
	}
	
	float u1=0, u2=0;
	u1 = s1 / avg1;
	u2 = s2 / avg2;
	float sigma1 = 0, sigma2 = 0;
	
	for (int i = 0; i < img.w; i++) // i: row index
	{
		for (int j = 0; j < img.h; j++) // j: column index
		{
			int val = cvRound(dst.at<uchar>(i + j*img.h));
			if ( (i + j*img.h) < t)
			{
				sigma1 += (u1 - (i + j*img.h))*(u1 - (i + j*img.h))*val;
			}
			else
			{
				sigma2 += (u2 - (i + j*img.h))*(u2 - (i + j*img.h))*val;
			}
		}
	}
	
	return sigma1 + sigma2; // 
}

__global__
void copy_back(uchar* dst, int* src, int h, int w, int scaler)
{
    int index = blockIdx.x *blockDim.x + threadIdx.x;
    if ( index < h*w ) {
	    dst[index] = (uchar)( src[index] / scaler);
    }
}

void Otsu_compute(int* buffer, uchar* oldimg, int h, int w, int r)
{
	// memcpy(oldimg.pixel, img.pixel, (std::size_t) sizeof(uchar)*img.w * img.h ); // memory copying. 從img.pixel陣列複製長度為sizeof(uchar)*img.w * img.h(整張圖片長乘寬的數值)
	uchar* dst = img.pixel;
	
	float min = OtsuPart(img.pixel, 0);
	
	int index=0;
	int minindex = 256;
	//printf("min:%f", min);
	// 先改出C版本，再改成CUDA，
	// 格式統一
	
	for (int i = 0; i < img.w; i++) // i: row index
	{
		for (int j = 0; j < img.h; j++) // j: column index
		{
			dst[i + j*img.w] = 0; // initialization of dst[]
			
			float val = OtsuPart(img.pixel, i + j*img.w);
			printf("val:%f\n", val);
			if (val - min < 0)
			{
				min = val;
				minindex = i + j*img.w;
				dst[minindex]=min;
			}
		}
	}
	
	//return minindex; // 目的，找最小值
}

void Otsu(bitmap &img) // Mat hist
{
	cudaError err; // 報錯用變數。
    uchar* pixel; // 整張圖，可以代表整張圖任一點的變數。
    uchar* oldpixel; // 舊圖，可以代表整張舊圖任一點的變數。
    int* buffer; // 緩衝, buffer，call by reference用。
    
	pixel = img.pixel; // 整張圖
    oldpixel = oldimg.pixel; // 整張舊圖
	
	err  = cudaMalloc(&buffer, sizeof(int)*img.w*img.h);
    CHECK_ERROR(err)
	
	Zero<<<(img.w * img.h + BLOCK_SIZE) / BLOCK_SIZE, BLOCK_SIZE>>>(buffer, img.h, img.w);
    CHECK_LAST_ERROR
	Otsu_compute<<<(img.w * img.h + BLOCK_SIZE) / BLOCK_SIZE, BLOCK_SIZE>>>(buffer, pixel, img.h, img.w, r);
    CHECK_LAST_ERROR

    copy_back<<<(img.w * img.h + BLOCK_SIZE) / BLOCK_SIZE, BLOCK_SIZE>>>(pixel, buffer, img.h, img.w, 1);
    CHECK_LAST_ERROR
	
	Zero<<<(img.w * img.h + BLOCK_SIZE) / BLOCK_SIZE, BLOCK_SIZE>>>(buffer, img.h, img.w);
    CHECK_LAST_ERROR
	Otsu_compute<<<(img.w * img.h + BLOCK_SIZE) / BLOCK_SIZE, BLOCK_SIZE>>>(buffer, pixel, img.h, img.w, r);
    CHECK_LAST_ERROR

    copy_back<<<(img.w * img.h + BLOCK_SIZE) / BLOCK_SIZE, BLOCK_SIZE>>>(pixel, buffer, img.h, img.w, 1);
    CHECK_LAST_ERROR
	
	
}