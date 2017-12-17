/* sobel.c */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define MAX_BRIGHTNESS 255

int weight_x[3][3] = {{ -1,  0,  1 },
		      { -2,  0,  2 },
		      { -1,  0,  1 }};

int weight_y[3][3] = {{ -1,  0,  1 },
		      { -2,  0,  2 },
		      { -1,  0,  1 }};

static void sobel_filtering_xy(unsigned char** image1, unsigned char** image2 ,int x_size1, int y_size1, int weight[3][3]);

void sobel_filtering(unsigned char** image1, unsigned char** image2 ,int x_size, int y_size)
{

    unsigned char** x_dim_ptr = new unsigned char*[y_size];
    unsigned char** y_dim_ptr = new unsigned char*[y_size];
    for(int i = 0; i < y_size; ++i) {
            x_dim_ptr[i] = new unsigned char[x_size];
            y_dim_ptr[i] = new unsigned char[x_size];
    }


    sobel_filtering_xy(image1, x_dim_ptr, x_size, y_size, weight_x);
    sobel_filtering_xy(image1, y_dim_ptr, x_size, y_size, weight_y);

    for (int y = 1; y < y_size - 1; y++) {
        for (int x = 1; x < x_size - 1; x++) {
            signed char _x = ((signed char) x_dim_ptr[y][x]) - MAX_BRIGHTNESS/2;
            signed char _y = ((signed char) y_dim_ptr[y][x]) - MAX_BRIGHTNESS/2;

            image2[y][x] = (unsigned char) sqrt( _x*_x + _y*_y);
            if (image2[y][x] < 1) {
                image2[y][x] = 0;
            } else {
                image2[y][x] = MAX_BRIGHTNESS;
            }
        }
    }
}


void sobel_filtering_xy(unsigned char** image1, unsigned char** image2 ,int x_size1, int y_size1, int weight[3][3])
     /* Spatial filtering of image data */
     /* Sobel filter (horizontal differentiation */
     /* Input: image1[y][x] ---- Outout: image2[y][x] */
{
  /* Definition of Sobel filter in horizontal direction */
  double pixel_value;
  double min, max;
  int x, y, i, j;  /* Loop variable */
  
  /* Maximum values calculation after filtering*/
//  printf("Now, filtering of input image is performed\n\n");
  min = DBL_MAX;
  max = -DBL_MAX;
  for (y = 1; y < y_size1 - 1; y++) {
    for (x = 1; x < x_size1 - 1; x++) {
      pixel_value = 0.0;
      for (j = -1; j <= 1; j++) {
	    for (i = -1; i <= 1; i++) {
	      pixel_value += weight[j + 1][i + 1] * image1[y + j][x + i];
	    }
      }
      if (pixel_value < min) min = pixel_value;
      if (pixel_value > max) max = pixel_value;
    }
  }
  if ((int)(max - min) == 0) {
    printf("Nothing exists!!!\n\n");
    exit(1);
  }

  /* Initialization of image2[y][x] */
  int x_size2 = x_size1;
  int y_size2 = y_size1;
  for (y = 0; y < y_size2; y++) {
    for (x = 0; x < x_size2; x++) {
      image2[y][x] = 0;
    }
  }
  /* Generation of image2 after linear transformtion */
  for (y = 1; y < y_size1 - 1; y++) {
    for (x = 1; x < x_size1 - 1; x++) {
      pixel_value = 0.0;
      for (j = -1; j <= 1; j++) {
	    for (i = -1; i <= 1; i++) {
	      pixel_value += weight[j + 1][i + 1] * image1[y + j][x + i];
	    }
      }
      pixel_value = MAX_BRIGHTNESS * (pixel_value - min) / (max - min);
      image2[y][x] = (unsigned char)pixel_value;
    }
  }
}

//main( )
//{
  //load_image_data( );   /* Input of image1 */ 
  //sobel_filtering( );   /* Sobel filter is applied to image1 */
  //save_image_data( );   /* Output of image2 */
//  return 0;
//}

