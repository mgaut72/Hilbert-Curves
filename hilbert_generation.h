#ifndef H_HILBERT_GENERATION
#define H_HILBERT_GENERATION

void step(int dir, int blen, int *s, int *x, int *y);

void binary(unsigned k, int len, char *s);

void hilbert(int dir, int rot, int order, int blen, int *s, int *x, int *y);

extern int verbose_generation;

#endif
