#include <stdio.h>
#include "hilbert_generation.h"
#include "hil_xy_from_s.h"

int verbose_generation; // hilbert_generation.h expects this for debug output

int main(int argc, char **argv){

    /*
     * hilbert curve generation
     */

    int x = -1, y = 0;          // coordinates
    int s = 0;                  // distance along curve
    int blen;                   // # significant digits of s
    int order;                  // order of hilbert curve
    verbose_generation = 1;

    order = 3;
    blen = order;
    step(0, blen, &s, &x, &y);
    hilbert(0,1,order, blen, &s, &x, &y);
    verbose_generation = 0;

    /*
     * coordinates form distance
     *
     * expected values based on output from hilbert generation
     */
    printf("\n\n");
    unsigned distance = 30;
    unsigned expected_x = 2,
             expected_y = 4;

    unsigned actual_x, actual_y;

    hil_xy_from_s(distance, order, &actual_x, &actual_y);

    printf("expected : (%d, %d)\nactual   : (%d, %d)\n",
            expected_x, expected_x, actual_x, actual_y);

    return 0;
}
