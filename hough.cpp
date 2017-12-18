#include <math.h>
#include <stdio.h>
#define SUB_CIRCLE 1

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

void HoughCircles(unsigned char** src, int rows, int cols, int MaxR, int MinR)
{
    int total_point;
    int valid_point;
    int valid_subcircle;
    int total_circle = 0;
    int _x, _y;
    bool stop;
    for (int y = MinR; y < rows; y++) {
        for (int x = MinR; x < cols; x++) {
            stop = false;
            valid_subcircle = 0;
            for (int r = MinR; r <= MaxR; r++) {
                if ( stop ) {
                    break;
                }
                total_point = 0;
                valid_point = 0;
                for ( float d = 0; d < 2 * M_PI; d += 0.3) {
                    _x = x + (int) r * cos(d);
                    _y = y + (int) r * sin(d);
                    if ( _x < 0 || _x >= cols || _y  < 0 || _y >= rows ) {
                        stop = true;
                        break;
                    }
                    total_point += 1;
                    valid_point += MIN(1, src[_y][_x]);
                    if ( 0 < MIN(1, src[y][x]) ) 
                        printf("| x: %d  y: %d r: %d data: %d\n", _x, _y, r, src[y][x]);

                }


                if ( total_point > 0 &&  valid_point / total_point > 0.6) {
                    valid_subcircle += 1;
                }

                if (valid_subcircle >= SUB_CIRCLE) {
                    printf("Circle #%d x: %d  y: %d r: %d\n", total_circle, x, y, r);
                    total_circle += 1;
                    stop = true;
                }
            }
        }
    }
}
