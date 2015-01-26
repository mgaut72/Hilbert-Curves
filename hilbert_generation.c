#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hilbert_generation.h"

hilbertStep* genHilbert(int order){
    hilbertStep *curve = malloc((1 + pow(4,order)) * sizeof(*curve));
    hilbertStep *curr = curve;


    /* initial conditions */
    int blen = order;
    int dir = 0;
    int rot = 1;
    curr->x = -1;
    curr->y = 0;
    curr->s = -1;

    curve++; // skip over initialization in our reported results

    step(dir, blen, &curr);

    hilbert(dir,rot,order, blen, &curr);

    return curve;
}




void hilbert(int dir, int rot, int order, int blen, hilbertStep **curr){
/* rot == rotation is either +/- 1 corresponding to clockwise or counter
 * dir = direction = 0,1,2,3 corresponding to right, up, left, down
 * order is the resolution of the curve we are currently at
 *
 *  ex.
 *          ┌──  start
 *          │
 *          └──  end
 *
 *      has direction down (3) due to the fact that the end is below the start
 *      has rotation counter-clockwise (-1) as there is such a traversal
 *          involved in going down
 */

    if (order == 0) return;

    /* each curve of a given order should be initialized with
     * dir = 0, rot = 1, but this works in general.
     *
     * Note that comments
     * are based on the assumptions given about the initial conditions,
     * which won't necessarily be true on the recusive steps
     */

    dir = dir + rot;                                // set dir to up
    hilbert(dir, -rot, order - 1, blen, curr);   // draw sub-curve up, ccw
    step(dir, blen, curr);                       // step up

    dir = dir - rot;                                // set dir to right
    hilbert(dir, rot, order - 1, blen, curr);    // sub-curve right, cw
    step(dir, blen, curr);                       // step right
    hilbert(dir, rot, order - 1, blen, curr);    // sub-curve right, cw

    dir = dir - rot;                                // set dir to down
    step(dir, blen, curr);                       // step down
    hilbert(dir, -rot, order - 1, blen, curr);   // sub-curve down, ccw
}


void step(int dir, int blen, hilbertStep **curr){

    *((*curr)+1) = **curr; // start the next the same as the current

    switch (dir & 3) {      // effectively modding by 4, but always positive
    // alter the coordinates assocaiated with this step
        case 0:
            ((*curr)+1)->x = (*curr)->x + 1; break;
        case 1:
            ((*curr)+1)->y = (*curr)->y + 1; break;
        case 2:
            ((*curr)+1)->x = (*curr)->x - 1; break;
        case 3:
            ((*curr)+1)->y = (*curr)->y - 1; break;
    }

    ((*curr)+1)->s = (*curr)->s + 1; // increment distance along curve

    if (verbose_generation){
        printStep(*(*curr + 1), blen);
    }

    (*curr)++; // move our pointer to the next element in the curve
}

void printStep(hilbertStep step, int blen){
    char ii[33], xx[17], yy[17];
    binary(step.s, 2*blen, ii);
    binary(step.x, blen, xx);
    binary(step.y, blen, yy);
    printf("%4d : %s %s %s\n", step.s, ii, xx, yy);
}

void binary(unsigned k, int len, char *s){
/* num -> string
 */

    int i;

    s[len] = 0;
    for(i = len - 1; i >= 0; i--){
        if (k & 1)
            s[i] = '1';
        else
            s[i] = '0';
        k = k>>1;
    }
}
