#include <stdio.h>
#include <stdio.h>
#include "hilbert_generation.h"

void hilbert(int dir, int rot, int order, int blen, int *s, int *x, int *y){
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
    hilbert(dir, -rot, order - 1, blen, s, x, y);   // draw sub-curve up, ccw
    step(dir, blen, s, x, y);                       // step up

    dir = dir - rot;                                // set dir to right
    hilbert(dir, rot, order - 1, blen, s, x, y);    // sub-curve right, cw
    step(dir, blen, s, x, y);                       // step right
    hilbert(dir, rot, order - 1, blen, s, x, y);    // sub-curve right, cw

    dir = dir - rot;                                // set dir to down
    step(dir, blen, s, x, y);                       // step down
    hilbert(dir, -rot, order - 1, blen, s, x, y);   // sub-curve down, ccw
}


void step(int dir, int blen, int *s, int *x, int *y){

    switch (dir & 3) {      // effectively modding by 4, but always positive
    // alter the coordinates assocaiated with this step
        case 0:
            (*x)++; break;
        case 1:
            (*y)++; break;
        case 2:
            (*x)--; break;
        case 3:
            (*y)--; break;
    }

    if (verbose_generation){
        char ii[33], xx[17], yy[17];
        binary(*s, 2*blen, ii);
        binary(*x, blen, xx);
        binary(*y, blen, yy);
        printf("%4d : %d %s %s %s\n", *s, dir & 3, ii, xx, yy);
    }

    (*s)++;
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
