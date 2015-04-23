#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "3D_hilbert_generation.h"
#include "turtle3D.h"

hilbertStep3D* genHilbert3D(int order){
    hilbertStep3D *curve = malloc(1 + (pow(8,order)) * sizeof(*curve));
    hilbertStep3D *curr = curve;


    /* initial conditions */
    curr->x = -1;
    curr->y = 0;
    curr->z = 0;
    curr->s = -1;

    orientation3D o = default_orientation3D;

    step3D(&curr, o);

    hilbert3D(o, order, &curr);

    curve++;

    return curve;
}




void hilbert3D(orientation3D o, int order, hilbertStep3D **curr){
    if (order == 0) return;

    o = pitch_up(o);
    o = roll_left(o);

    hilbert3D(o,order-1, curr);

    step3D(curr, o);

    o = pitch_up(o);
    o = roll_left(o);

    hilbert3D(o,order-1, curr);

    step3D(curr, o);

    hilbert3D(o,order-1, curr);

    o = turn_right(o);

    step3D(curr, o);

    o = pitch_up(o);
    o = roll_right(o);
    o = roll_right(o);

    hilbert3D(o,order-1, curr);

    step3D(curr, o);

    hilbert3D(o,order-1, curr);

    o = pitch_down(o);

    step3D(curr, o);

    o = turn_left(o);
    o = roll_right(o);
    o = roll_right(o);

    hilbert3D(o,order-1, curr);

    step3D(curr, o);

    hilbert3D(o,order-1, curr);

    o = turn_right(o);

    step3D(curr, o);

    o = roll_right(o);

    hilbert3D(o,order-1, curr);

    o = turn_right(o);
    o = roll_right(o);
}


void step3D(hilbertStep3D **curr, orientation3D o){

    printf("\nentering step\n");
    printf("heading = [%d, %d, %d]\n", o.heading[0], o.heading[1], o.heading[2]);
    printf("position %d = [%d, %d, %d]\n", (*curr)->s, (*curr)->x, (*curr)->y, (*curr)->z);

    *((*curr)+1) = **curr; // start the next the same as the current

    if(o.heading[0] != 0)
        ((*curr)+1)->x = (*curr)->x + o.heading[0];
    else if(o.heading[1] != 0)
        ((*curr)+1)->y = (*curr)->y + o.heading[1];
    else if(o.heading[2] != 0)
        ((*curr)+1)->z = (*curr)->z + o.heading[2];

    ((*curr)+1)->s = (*curr)->s + 1; // increment distance along curve

    (*curr)++; // move our pointer to the next element in the curve
    printf("position %d = [%d, %d, %d]\n", (*curr)->s, (*curr)->x, (*curr)->y, (*curr)->z);
    printf("\nexiting step\n");
}
