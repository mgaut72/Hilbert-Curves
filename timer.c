#include <time.h>
#include<sys/time.h>
 
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif
 
#include"timer.h"

/* \fn double timer(void)
 * \brief Returns accurate wall clock timer.*/ 
double timer(void)
{
#ifndef MICROSEC
  return timer_nsec();
#else  /*MICROSEC*/
  return timer_usec();
#endif /*MICROSEC*/
}

/* \fn double timer_usec(void)
 * \brief Wall clock timer accurate to a microsecond. */
double timer_usec(void)
{
  struct timeval te;
  gettimeofday(&te,NULL);
  return te.tv_sec + 1.0e-6*te.tv_usec;
}

/* \fn double timer_nsec(void)
 * \brief Wall clock timer accurate to a nanosecond. */
double timer_nsec(void)
{
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mtp;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mtp);
  mach_port_deallocate(mach_task_self(), cclock);
  return mtp.tv_sec + 1.0e-9*mtp.tv_nsec;
#else
  struct timespec tp;
  clock_gettime(CLOCK_REALTIME, &tp);
  return tp.tv_sec + 1.0e-9*tp.tv_nsec;
#endif
 
}
