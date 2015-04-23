#ifndef H_HILBERT_GENERATION_3D
#define H_HILBERT_GENERATION_3D

typedef struct {
    int s;
    int x;
    int y;
    int z;
} hilbertStep3D;

typedef struct {
    int[] heading = {1,0,0};    // start going forward (x direction)
    int[] left    = {0,1,0};    // left is the y direction
    int[] up      = {0,0,1};    // start as up in the z dir
}  orientation3D;


hilbertStep* genHilbert(int order);

void step(int dir, int blen, hilbertStep **curr);

void binary(unsigned k, int len, char *s);

void hilbert(int dir, int rot, int order, int blen, hilbertStep **curr);

void printStep(hilbertStep step, int blen);

extern int verbose_generation;

#endif
