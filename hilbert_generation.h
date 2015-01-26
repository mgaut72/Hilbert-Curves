#ifndef H_HILBERT_GENERATION
#define H_HILBERT_GENERATION

typedef struct {
    int s;
    int x;
    int y;
} hilbertStep;

hilbertStep* genHilbert(int order);

void step(int dir, int blen, hilbertStep **curr);

void binary(unsigned k, int len, char *s);

void hilbert(int dir, int rot, int order, int blen, hilbertStep **curr);

void printStep(hilbertStep step, int blen);

extern int verbose_generation;

#endif
