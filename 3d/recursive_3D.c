#include <stdio.h>
#include <math.h>

#include "3D_hilbert_generation.h"

void printCurve(hilbertStep3D *curve, int curve_length);

int main(int argc, char **argv){

    int order = 1;

    int curve_length = pow(8, order);

    hilbertStep3D *curve = genHilbert3D(order);

    printCurve(curve, curve_length);

    return 0;
}

void printCurve(hilbertStep3D *curve, int curve_length){
    int i;
    for(i = 0; i < curve_length; i++){
        printf("%d: (%d, %d, %d)\n", curve[i].s, curve[i].x, curve[i].y,
                curve[i].z);
    }
}


