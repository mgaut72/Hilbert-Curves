#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
//#include "parallel_prefix.h"
/* familiarity with the derivation of the lam-shapiro method is recommended
 * before attempting to understanding the derivation of the parallel prefix
 * method, as parallel prefix relies on the same perspective of the structure
 * of the curve that lam-shapiro considers.
 *
 * (0,1) = 01 = 1 ┌───┐2 = 10 = (1,1)
 *                │   │
 * (0,0) = 00 = 0 │   │3 = 11 = (1,0)
 *
 */
#define BUF_SIZE 33

void int2bin(int i, char *str, size_t bits)
{

    // type punning because signed shift is implementation-defined
    unsigned u = *(unsigned *)&i;
    for(; bits--; u >>= 1)
        str[bits] = u & 1 ? '1' : '0';
}


int main(void){

    // for printing binary strings
    size_t bits = sizeof(int) * CHAR_BIT;
    char * str = malloc(bits + 1);
    if(!str) return 1;
    str[bits] = 0;

    unsigned s;
    int n;
    unsigned xp, yp;

    s = 12;
    n = 2;

    int2bin(s,str,bits);
    printf("initially s = %s\n", str);

    unsigned comp,  // bits that determine when we need to complement x,y
             swap,  // bits that determine when we need to swap x,y
             cs,    // intermediate value to calculate  comp & swap
             t,     // something
             sr;    // eeerrrrr... something else


    /* pad s for the purpose of calculating the swap and complement values.
     * 01 has no effect on the swap and complement values calculated from s
     * so we pad wtih 0x5 = 0101
     */
    s = s | (0x55555555 << 2*n); // shift by 2n - each order == 2 bits

    int2bin(s,str,bits);
    printf("after padding s = %s\n", str);

    /* all the even bits of s are in teh odd bits of sr.
     * the even bits of sr are 0
     */
    sr = (s >> 1) & 0x55555555;

    int2bin(sr,str,bits);
    printf("sr = %s\n", str);

    int2bin(((s & 0x55555555)) ,str,bits);
    printf("s & 0x5..5 = %s\n", str);
    int2bin(((s & 0x55555555) + sr) ,str,bits);
    printf("almost cs = %s\n", str);

    /* (s & 0x55555555) is all the odd bits of s with nothing in evens
     * sr is all the even bits of s in the odd spots, nothing in the evens
     *
     * Consider the least significant pair of bits of cs
     * the first (least significant) bit will be 0 when s_{2i} == s_{2i+1}
     * the second bit will be zero unless both s_{2i} == s_{2i+1} == 1
     *
     * This is exactly the definition of S_i and C_i in figure 16-7 of
     * hacker's delight
     */
    cs = ((s & 0x55555555) + sr) ^ 0x55555555;

    int2bin(cs,str,bits);
    printf("cs before propogation = %s\n", str);

    /* at this point cs has only been taken into account be how it is effected
     * by the bits of S. however, there is also a propogation within cs
     * where we get that cs_i is effected by cs_{i+1}, the 2 bits to the left
     *
     * in the circuit that describes how C_i is effected by c_{i-1}
     * we see that
     *
     *      C_i = C_{i+1} XOR <influence from s>
     *      S_i = S_{i+1} XOR <influence from s>
     *
     * since we have already accounted for the influence from S, we perform
     * as series of shifts and ORs to account for the propogation of CS
     * on itself
     */
    cs = cs ^ (cs >> 2);
    int2bin(cs,str,bits);
    printf("cs propogation 2 = %s\n", str);

    cs = cs ^ (cs >> 4);
    int2bin(cs,str,bits);
    printf("cs propogation 4 = %s\n", str);

    cs = cs ^ (cs >> 8);
    int2bin(cs,str,bits);
    printf("cs propogation 8 = %s\n", str);

    cs = cs ^ (cs >> 16);
    int2bin(cs,str,bits);
    printf("cs propogation 16 = %s\n", str);


    /* at this point cs is of the form
     *  cscs...cs where each 'c' is the complement bit for that step
     *              and each 's' is the swap bit for that step
     *
     *  so now we seperate them into 0s0s0s0s and 0c0c0c0c
     *
     *  now each pair of bits of swap and each pair of bits
     *  of comp indicate how to transform the given step
     */
    swap = cs & 0x55555555;
    comp = (cs >> 1) & 0x55555555;

    int2bin(swap,str,bits);
    printf("swap = %s\n", str);

    int2bin(comp,str,bits);
    printf("comp = %s\n", str);


    int2bin(s & swap,str,bits);
    printf("s & swap = %s\n", str);

    t = (s & swap) ^ comp;

    int2bin(t,str,bits);
    printf("t = %s\n", str);

    int2bin(t << 1,str,bits);
    printf("t << 1= %s\n", str);

    int2bin(t ^ (t << 1),str,bits);
    printf("t ^ t << 1= %s\n", str);

    int2bin(s,str,bits);
    printf("pre s = %s\n", str);

    int2bin(s,str,bits);
    printf("s ^ sr = %s\n", str);

    /* s ^ sr is the XOR with s_{2i + 1}
     * and since sr is the even bits of s, in the odd spots of sr
     * and 0 in the even bits of sr, this includes the shor of s_{2i}
     * for the y bits
     *
     * finally t ^ (t << 1) ensures that both the x bit and the y bit
     * get the common compenent that t represents in Figure 16-7
     *
     */
    s = s ^ sr ^ t ^ (t << 1);

    int2bin(s,str,bits);
    printf("padded s = %s\n", str);

    /* has the effect of unpadding s to only be 2n bits
     *
     * ((1 << 2*n) - 1) will be 0...01..1 where there are 2n ones
     */
    s = s & ((1 << 2*n) - 1);

    int2bin(s,str,bits);
    printf("unpadded s = %s\n", str);

    /* Now "unshuffle" to separate the x and y bits.
     *
     * x is in the odd bits
     * y is in the even bits
     *
     * 0x22222222 == 0010 0010 0010 0010 0010 0010 0010 0010
     * 0x0c0c0c0c == 0000 1100 0000 1100 0000 1100 0000 1100
     * 0x00F000F0 == 0000 0000 1111 0000 0000 0000 1111 0000
     * 0x0000FF00 == 0000 0000 0000 0000 1111 1111 0000 0000
     *
     * No magic here as far as Hilbert Curves are concerned.  This is just a
     * pretty standard way to unshuffle bits
     */
    t = (s ^ (s >> 1)) & 0x22222222; s = s ^ t ^ (t << 1);
    int2bin(s,str,bits);
    printf("s = %s\n", str);
    t = (s ^ (s >> 2)) & 0x0C0C0C0C; s = s ^ t ^ (t << 2);
    int2bin(s,str,bits);
    printf("s = %s\n", str);
    t = (s ^ (s >> 4)) & 0x00F000F0; s = s ^ t ^ (t << 4);
    int2bin(s,str,bits);
    printf("s = %s\n", str);
    t = (s ^ (s >> 8)) & 0x0000FF00; s = s ^ t ^ (t << 8);
    int2bin(s,str,bits);
    printf("s = %s\n", str);

    xp = s >> 16; // Assign the two halves
    int2bin(xp,str,bits);
    printf("x = %s\n", str);

    yp = s & 0xFFFF; // of s to x and y.
    int2bin(yp,str,bits);
    printf("y = %s\n", str);

    return 0;

}
