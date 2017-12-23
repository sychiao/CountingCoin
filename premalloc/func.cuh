#include "func.h"

extern __device void* d_buffer;

__global__
void copy_back(uchar* dst, int* src, int h, int w, int scaler);
