#include "func.h"
void TimeDiff(struct  timeval* start, struct  timeval* end)
{
    gettimeofday(end,NULL);
    long diff = 1000000 * (end->tv_sec-start->tv_sec)+ end->tv_usec-start->tv_usec;
    double out = diff / (double) 1000000;
    memcpy(start, end, sizeof(struct timeval));
    printf("%lf\n",out);
}
