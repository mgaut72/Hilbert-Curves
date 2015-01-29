#ifndef TIMER_H
#define TIMER_H
#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/

/* \fn double timer(void)
 * \brief Returns accurate wall clock timer.*/ 
double timer(void);


/* \fn double timer_usec(void)
 * \brief Wall clock timer accurate to a microsecond. */
double timer_usec(void);

/* \fn double timer_nsec(void)
 * \brief Wall clock timer accurate to a nanosecond. */
double timer_nsec(void);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*TIMER_H*/
