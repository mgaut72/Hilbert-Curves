void hil_xy_from_s(unsigned s, int n, unsigned *xp, unsigned *yp){
/* s is the distance along the hilbert curve
 *      should be padded with leading zeros to length 2n
 * n is the order of the hilbert curve
 *
 * returns : xp, yp are the coords that correspond to the distance given by s
 */

    int i;
    unsigned state,     // state in transition table 0..3
             x, y,      // intermediate coordinate computations
             row;       // row in transition table.  bitmagic used for lookups

    state = 0;
    x = y= 0;

    for (i = 2*n - 2; i >= 0; i -= 2){
    /* loop consider n pairs of bits of s
     */

        row = 4 * state     // since there are 4 rows per state
            | (s >> i) & 3; // get to the 2 bits of s we are considering


        x = (x << 1) | (0x936C >> row) & 1; // TODO, figure out these
        y = (y << 1) | (0x39C6 >> row) & 1; //       magic numbers
        state = (0x3E6B94C1 >> 2*row) & 3;
    }

    *xp = x;
    *yp = y;
}
