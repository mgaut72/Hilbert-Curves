#include <stdio.h>
#include "hilbert_generation.h"

int verbose_generation;

int main(int argc, char **argv){
    int order;
    if (argc != 2){
        printf("expected the order as a command line argument\n");
        return 1;
    }

    /*
     * hilbert curve generation
     */

    int x = -1, y = 0;          // coordinates
    int s = 0;                  // distance along curve
    int blen;                   // # significant digits of s
    verbose_generation = 1;

    order = atoi(argv[1]);
    blen = order;
    step(0, blen, &s, &x, &y);
    hilbert(0,1,order, blen, &s, &x, &y);
    return 0;
}
