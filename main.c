#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hilbert_generation.h"
#include "hil_xy_from_s.h"
#include "lam_shapiro.h"
#include "parallel_prefix.h"
#include "timer.h"

int verbose_generation; // hilbert_generation.h expects this for debug output
int verbose_testing;
int verify(hilbertStep *curve, int distance, int x, int y);


int main(int argc, char **argv){

    if(argc != 2){
        printf("expected curve order as command line argument\n");
        return 1;
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
     * coordinates from distance using the iterative left to right method
     *
     * expected values based on output from hilbert generation
     */
    unsigned distance, x, y;
    int i;

    distance = x = y = 0;
    t_start = timer();
    for(i = 0; i < pow(4, order); i++){
        hil_xy_from_s(i, order, &x, &y);
        if (verify(curve, i, x, y)){
            break;
        }
    }
    t_stop  = timer();
    printf("state table based curve verification time %e\n", t_stop - t_start);

    /*
     * coordinates from distance using the lam shapiro method
     */
    distance = x = y = 0;
    t_start = timer();
    for(i = 0; i < pow(4, order); i++){
        hil_xy_from_s_ls(i, order, &x, &y);
        if (verify(curve, i, x, y)){
            break;
        }
    }
    t_stop  = timer();
    printf("Lam-Shapiro curve verification time %e\n", t_stop - t_start);

    /*
     * coordinates from distance using the parallel prefix method
     */
    distance = x = y = 0;
    t_start = timer();
    for(i = 0; i < pow(4, order); i++){
        hil_xy_from_s_pp(i, order, &x, &y);
        if (verify(curve, i, x, y)){
            break;
        }
    }
    t_stop  = timer();
    printf("parallel prefix curve verification time %e\n", t_stop - t_start);

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
        printf("expected %d, got %d\n", distance, tmp->s);
        retval = 1;
    }

    if(x != tmp->x){
        printf("ERROR, x mismatch\n");
        printf("expected %d, got %d\n", x, tmp->x);
        retval = 1;
    }

    if(y != tmp->y){
        printf("ERROR, y mismatch\n");
        printf("expected %d, got %d\n", y, tmp->y);
        retval = 1;
    }

    return retval;
}





