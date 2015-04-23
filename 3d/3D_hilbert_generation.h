#ifndef H_HILBERT_GENERATION_3D
#define H_HILBERT_GENERATION_3D

#include "turtle3D.h"

typedef struct {
    int s;
    int x;
    int y;
    int z;
} hilbertStep3D;

hilbertStep3D* genHilbert3D(int order);

void step3D(hilbertStep3D **curr, orientation3D o);

void hilbert3D(orientation3D o, int order, hilbertStep3D **curr);

#endif
