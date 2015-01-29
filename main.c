#include <stdio.h>
#include <math.h>
#include "hilbert_generation.h"
#include "hil_xy_from_s.h"
#include "timer.h"

int verbose_generation; // hilbert_generation.h expects this for debug output
int verbose_testing;

int main(int argc, char **argv){

    if(argc != 2){
        printf("expected curve order as command line argument\n");
        return;
    }

    double t_start, t_stop; // timer variables

    /*
     * hilbert curve generation
     */

    int order = atoi(argv[1]);                  // order of hilbert curve
    printf("generating a curve of order %d\n", order);

    verbose_generation = 0;
    t_start = timer();
    hilbertStep *curve = genHilbert(order);
    t_stop  = timer();
    printf("curve generation time %e\n", t_stop - t_start);

    /*
     * coordinates form distance
     *
     * expected values based on output from hilbert generation
     */
    unsigned distance, x, y;

    t_start = timer();
    printf("testing the coordinate calculation for each point\n");
    int i;
    for(i = 0; i < pow(4, order); i++){
        hil_xy_from_s(i, order, &x, &y);
        if (verify(curve, i, x, y)){
            break;
        }
    }
    t_stop  = timer();
    printf("curve verification time %e\n", t_stop - t_start);

    return 0;
}

int verify(hilbertStep *curve, int distance, int x, int y){
    hilbertStep *tmp = curve;
    tmp += distance;

    if(verbose_testing){
        printf("actual s = %d, x = %d, y = %d\n", tmp->s, tmp->x, tmp->y);
        printf("calculated s = %d, x = %d, y = %d\n", distance, x, y);
    }

    int retval = 0;

    if(distance != tmp->s){
        printf("ERROR, distance mismatch\n");
        retval = 1;
    }

    if(x != tmp->x){
        printf("ERROR, x mismatch\n");
        retval = 1;
    }

    if(y != tmp->y){
        printf("ERROR, y mismatch\n");
        retval = 1;
    }

    return retval;
}





