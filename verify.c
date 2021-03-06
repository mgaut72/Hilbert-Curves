#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hilbert_generation.h"
#include "hil_xy_from_s.h"
#include "hil_s_from_xy.h"
#include "lam_shapiro.h"
#include "reverse_lam_shapiro.h"
#include "parallel_prefix.h"

int verbose_generation; // hilbert_generation.h expects this for debug output
int verbose_testing;

int verify(hilbertStep *curve, int distance, int x, int y);

int main(int argc, char **argv){

    if(argc < 2){
        fprintf(stderr, "expected curve order as command line argument\n");
        return 1;
    }

    int repititions = 1;
    if(argc > 2)
        repititions = atoi(argv[2]);

    /*
     * hilbert curve generation
     */

    int order = atoi(argv[1]);                  // order of hilbert curve
    fprintf(stderr, "generating a curve of order %d\n", order);

    verbose_generation = 0;
    hilbertStep *curve = genHilbert(order);
    fprintf(stderr, "recursive curve generated\n");

    /*
     * coordinates from distance using the iterative left to right method
     *
     * expected values based on output from hilbert generation
     */
    unsigned x, y, s;
    int i,j;

    for(j = 0; j < repititions; j++){
        x = y = 0;
        for(i = 0; i < pow(4, order); i++){
            hil_xy_from_s(i, order, &x, &y);
            if (verify(curve, i, x, y)){
                break;
            }
        }
    }
    printf("state_table method verified\n");

    /*
     * coordinates from distance using the lam shapiro method
     */
    for(j = 0; j < repititions; j++){
        x = y = 0;
        //fprintf(stderr, "testing the coordinate calculation for each point\n");
        for(i = 0; i < pow(4, order); i++){
            hil_xy_from_s_ls(i, order, &x, &y);
            if (verify(curve, i, x, y)){
                break;
            }
        }
    }
    printf("Lam-Shapiro verified\n");

    /*
     * coordinates from distance using the parallel prefix method
     */
    for(j = 0; j < repititions; j++){
        x = y = 0;
        //fprintf(stderr, "testing the coordinate calculation for each point\n");
        for(i = 0; i < pow(4, order); i++){
            hil_xy_from_s_pp(i, order, &x, &y);
            if (verify(curve, i, x, y)){
                break;
            }
        }
    }
    printf("parallel_prefix verified\n");


    /*
     * test xy -> s conversions
     *
     * state table
     *
     * we know that given the order, the maximal x and y is ((2^order) - 1)
     */
    for(j = 0; j < repititions; j++){
        for(x = 0; x < pow(2,order)-1; x++){
            for(y = 0; y < pow(2,order)-1; y++){
                s = hil_s_from_xy(x,y,order);
                if (verify(curve, s, x, y)){
                    break;
                }
            }
        }
    }
    printf("reverse state table verified\n");

    /*
     * test xy -> s conversions
     *
     * lam shapiro
     */
    for(j = 0; j < repititions; j++){
        for(x = 0; x < pow(2,order)-1; x++){
            for(y = 0; y < pow(2,order)-1; y++){
                s = hil_s_from_xy_ls(x,y,order);
                if (verify(curve, s, x, y)){
                    break;
                }
            }
        }
    }
    printf("reverse lam shapiro verified\n");

    return 0;
}

int verify(hilbertStep *curve, int distance, int x, int y){
    hilbertStep *tmp = curve;
    tmp += distance;

    if(verbose_testing){
        printf("actual s = %d, x = %d, y = %d\n", tmp->s, tmp->x, tmp->y);
        printf("calculated s = %d, x = %d, y = %d\n", distance, x, y);
    }

    if(distance != tmp->s){
        fprintf(stderr, "ERROR, distance mismatch\n");
        fprintf(stderr, "expected %d, got %d\n", distance, tmp->s);
        return 1;
    }

    if(x != tmp->x){
        fprintf(stderr, "ERROR, x mismatch\n");
        fprintf(stderr, "expected %d, got %d\n", x, tmp->x);
        return 1;
    }

    if(y != tmp->y){
        fprintf(stderr, "ERROR, y mismatch\n");
        fprintf(stderr, "expected %d, got %d\n", y, tmp->y);
        return 1;
    }

    return 0;
}





