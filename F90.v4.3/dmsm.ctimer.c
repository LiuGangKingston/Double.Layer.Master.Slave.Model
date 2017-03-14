#include <time.h>


double dmsm_c_timer_(){
 struct timespec t_temp;
 double l;
 clock_gettime(CLOCK_REALTIME, &t_temp);
 l=(double)((double)t_temp.tv_sec+
   ((double)(t_temp.tv_nsec))/((double)1000000000L));
 return(l);
}

