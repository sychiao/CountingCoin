#include "func.h"
void TimeDiff(struct  timeval start, struct  timeval end)
{
    long diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    double out = diff / (double) 1000000;
    printf("%lf\n",out);
}
