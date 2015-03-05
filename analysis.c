#include <stdio.h>
#include <stdlib.h>
#include "hilbert_generation.h"
#include "hil_xy_from_s.h"
#include "lam_shapiro.h"
#include "parallel_prefix.h"
#include "timer.h"

int verbose_generation = 0; // hilbert_generation.h expects for debug output
int verbose_testing = 0;

int main(int argc, char **argv){

    if(argc < 2){
        fprintf(stderr, "expected maximal curve order as command line argument\n");
        return 1;
    }
    int max_order = atoi(argv[1]);

    int repititions = 2147483647;   // max integer
    if(argc > 2)
        repititions = atoi(argv[2]);

    double t_start, t_stop; // timer variables

    /*
     * coordinates from distance using the iterative left to right method
     *
     * expected values based on output from hilbert generation
     */
    unsigned s,     // distance we are testing with
             x, y;  // return value for our coordinates
    int i;


    int order;
    s = 1;
    for(order = 1; order <= max_order; order++){

        printf("order %d\n", order);

        t_start = timer();
        for(i = 0; i < repititions; i++){
            hil_xy_from_s(i, order, &x, &y);
        }
        t_stop  = timer();
        printf("state_table %e\n", t_stop - t_start);

        /*
         * coordinates from distance using the lam shapiro method
         */
        t_start = timer();
        for(i = 0; i < repititions; i++){
            hil_xy_from_s_ls(i, order, &x, &y);
        }
        t_stop  = timer();
        printf("Lam-Shapiro %e\n", t_stop - t_start);

        /*
         * coordinates from distance using the parallel prefix method
         */
        t_start = timer();
        for(i = 0; i < repititions; i++){
            hil_xy_from_s_ls(i, order, &x, &y);
        }
        t_stop  = timer();
        printf("parallel_prefix %e\n", t_stop - t_start);

        printf("\n");
    }

    return 0;
}
