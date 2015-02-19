#include "hil_xy_from_s.h"

/*
 * this algorithm for calculating the spacial coordinates depends on a table
 * which can be found in Hacker's Delight (/doc/hackers_delight_ch16.pdf).
 *
 * The table given on page 7 of the document (labeled "page 2 of 6") gives us
 * the notion of a state and how to build our coordinates based on the state
 * and the current two bits of the distance.  Using these conditions, it tells
 * us which bit to append to both the x and y coordinate.
 *
 * Take the "append to x" column on the table/value:
 * Note that 0x936C is 1001 0011 0110 1100
 *                     ^                 ^
 *                     15th bit        0th bit
 *
 * The ith is the bit we append to the x coordinate when the conditions for the
 * ith row of the Hacker's Delight table are satisfied.
 *
 * The same goes for the y coordinate.
 *
 * The functions use the current row to isolate the bit we will need to append
 * to each of our coordinates
 */
#define APPEND_TO_X_COLUMN  0x936C
#define APPEND_TO_Y_COLUMN  0x39C6
#define X_LOOKUP(row)       ((APPEND_TO_X_COLUMN >> row) & 1)
#define Y_LOOKUP(row)       ((APPEND_TO_Y_COLUMN >> row) & 1)

/* The state transition column is encoded similiarly to the coordinate columns.
 *
 * We first note that row will be 0..15, which corresponds to the row
 * of the table we are in.  State is 0..3, corresponding to A..D
 *
 * Because since there are 4 states, we need 2 bits to represent the state.
 *      00 = state 0
 *      01 = state 1
 *      ...
 *      11 = state 3
 *
 * note that 0x3E6B94C1 is
 *      00 11 11 10 01 10 10 11 10 01 01 00 11 00 00 01
 *      ^                                             ^
 *      row 15                                        row 0
 *
 * which when translated to states exactly corresponds to the table in the book
 *
 * the lookup function multiplies by 2 and ANDs by 3 since the state is encoded
 * with 2 bits
 */
#define STATE_TRANSITION_COLUMN 0x3E6B94C1
#define STATE_LOOKUP(row)       ((STATE_TRANSITION_COLUMN >> 2 * row) & 3)


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
             row;       // row in transition table.  bitmagic used for lookup

    state = 0;
    x = y= 0;

    for (i = 2*n - 2; i >= 0; i -= 2){
    /* loop consider n pairs of bits of s */

        row = 4 * state     // since there are 4 rows per state
            | ((s >> i) & 3); // get to the 2 bits of s we are considering


        /* use the table to lookup and append to x,y and then change state */
        x = (x << 1) | X_LOOKUP(row);
        y = (y << 1) | Y_LOOKUP(row);
        state = STATE_LOOKUP(row);
    }

    *xp = x;
    *yp = y;
}
