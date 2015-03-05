#include "parallel_prefix.h"
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

inline void hil_xy_from_s_pp(unsigned s, int n, unsigned *xp, unsigned *yp){

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

    sr = (s >> 1) & 0x55555555;
    cs = ((s & 0x55555555) + sr) ^ 0x55555555;

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
    cs = cs ^ (cs >> 4);
    cs = cs ^ (cs >> 8);
    cs = cs ^ (cs >> 16);

    /* at this point cs is of the form
     *  cscs...cs where each 'c' is the complement bit for that step
     *              and each 's' is the swap bit for that step
     *
     *  so now we seperate them into sssssss and cccccccc
     */
    swap = cs & 0x55555555;
    comp = (cs >> 1) & 0x55555555;



    t = (s & swap) ^ comp;
    s = s ^ sr ^ t ^ (t << 1);

    s = s & ((1 << 2*n) - 1);

    /* Now "unshuffle" to separate the x and y bits.
     *
     * x is in the odd bits
     * y is in the even bits
     *
     * 0x22222222 == 0010 0010 0010 0010 0010 0010 0010 0010
     * 0x0c0c0c0c == 0000 1100 0000 1100 0000 1100 0000 1100
     * 0x00F000F0 == 0000 0000 1111 0000 0000 0000 1111 0000
     * 0x0000FF00 == 0000 0000 0000 0000 1111 1111 0000 0000
     */
    t = (s ^ (s >> 1)) & 0x22222222; s = s ^ t ^ (t << 1);
    t = (s ^ (s >> 2)) & 0x0C0C0C0C; s = s ^ t ^ (t << 2);
    t = (s ^ (s >> 4)) & 0x00F000F0; s = s ^ t ^ (t << 4);
    t = (s ^ (s >> 8)) & 0x0000FF00; s = s ^ t ^ (t << 8);

    *xp = s >> 16; // Assign the two halves
    *yp = s & 0xFFFF; // of t to x and y.
}
