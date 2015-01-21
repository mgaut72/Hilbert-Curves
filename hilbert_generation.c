#include <stdio.h>
#include <stdio.h>

int x = -1;     // globals
int y = 0;

int s = 0;      // distance along the hilbert curve

int blen;       // length to print


void step(int dir);
void binary(unsigned k, int len, char *s);
void hilbert(int dir, int rot, int order);

void hilbert(int dir, int rot, int order){
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
     * are based on the assumptions given about the initial conditions
     */

    dir = dir + rot;                // set dir to up
    hilbert(dir, -rot, order - 1);  // draw sub-curve up, counterclockwise
    step(dir);                      // step up

    dir = dir - rot;                // set dir to right
    hilbert(dir, rot, order - 1);   // draw sub-curve right, clockwise
    step(dir);                      // step right
    hilbert(dir, rot, order - 1);   // draw sub-curve right, clockwise

    dir = dir - rot;                // set dir to down (its modular)
    step(dir);                      // step down
    hilbert(dir, -rot, order - 1);  // draw sub-curve down, counterclockwise
}


void step(int dir){
    char ii[33], xx[17], yy[17];

    switch (dir & 3) {      // effectively modding by 4, but always positive
    // alter the coordinates assocaiated with this step
        case 0:
            x++; break;
        case 1:
            y++; break;
        case 2:
            x--; break;
        case 3:
            y--; break;
    }
    binary(s, 2*blen, ii);
    binary(x, blen, xx);
    binary(y, blen, yy);

    printf("%4d : %d %s %s %s\n", s, dir & 3, ii, xx, yy);
    s++;
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

int main(int argc, char **argv){
    int order;
    if (argc != 2){
        printf("expected the order as a command line argument\n");
        return 1;
    }

    order = atoi(argv[1]);
    blen = order;
    hilbert(0,1,order);
    return 0;
}
