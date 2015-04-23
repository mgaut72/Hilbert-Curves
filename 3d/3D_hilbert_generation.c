#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "3d_hilbert_generation.h"
#include "turtle3d.h"

hilbertStep* genHilbert3D(int order){
    hilbertStep *curve = malloc((pow(8,order)) * sizeof(*curve));


    /* initial conditions */
    curve->x = 0;
    curve->y = 0;
    curve->z = 0;
    curve->s = 0;

    orientation3D o = default_orientation3D();

    hilbert(o, order, blen, &curr);

    return curve;
}




void hilbert(orientation3D o, int order, hilbertStep **curr){
    if (order == 0) return;

    o = pitch_up(o);
    o = roll_left(o);

    hilbert(o,order-1, curr);

    step(curr, o);

    o = pitch_up(o);
    o = roll_left(o);

    hilbert(o,order-1, curr);

    step(curr, o);

    hilbert(o,order-1, curr);

    o = turn_right(o);

    step(curr, o);

    o = pitch_up(o);
    o = roll_right(o);
    o = roll_right(o);

    hilbert(o,order-1, curr);

    step(curr, o);

    hilbert(o,order-1, curr);

    o = pitch_down(o);

    step(curr, o);

    o = turn_left(o);
    o = roll_right(o);
    o = roll_right(o);

    hilbert(o,order-1, curr);

    step(curr, o);

    hilbert(o,order-1, curr);

    o = turn_right(o);

    step(curr, o);

    o = roll_right(o);

    hilbert(o,order-1, curr);

    o = turn_right(o);
    o = roll_right(o);
}


void step(hilbertStep **curr, orientation3D o){

    *((*curr)+1) = **curr; // start the next the same as the current


    if(o.heading[0] != 0)
            ((*curr)+1)->x = (*curr)->x + o.heading[0];
    else if(o.heading[1] != 0)
            ((*curr)+1)->y = (*curr)->y + o.heading[1];
    else if(o.heading[2] == 0)
            ((*curr)+1)->z = (*curr)->z + o.heading[2];

    ((*curr)+1)->s = (*curr)->s + 1; // increment distance along curve

    (*curr)++; // move our pointer to the next element in the curve
}
