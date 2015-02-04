#include "lam_shapiro.h"
/* Since there is a recursive nature to the hilbert
 * curve, we will talk about the different resolutions.  Order 1 is the lowest
 * resolution, order 2 is slightly higher resolution, etc.
 *
 * This method starts by finding out information about the highest-resolution
 * sub-curve we are in, and then uses the transformations related to the
 * relationship between the order n+1 and 4 order n curves.
 *
 * The rightmost two bits will tell us which position along the highest
 * resolution sub-quadrant we are at.  This is the baseline configuration
 * for an order 1 hilbert curve with points labeled according to their
 * distance.
 *
 *       1 ┌──┐2
 *       0 │  │3
 *
 * recall that an order 2 hilbert curve consists of 4 order 1 hilbert curves
 *
 *                ┌──┐   ┌──┐
 *                │1 │   │ 2│
 *                │  └───┘  │
 *                │         │
 *                └──┐   ┌──┘
 *                 0 │   │ 3
 *                ───┘   └──
 *
 * observe that the 1 and 2 curves are in the same orientation as the first
 * order curve, which is why there is no transformation on the coordinate
 * of x,y when the curve is positon 1 or 2
 *
 * position zero involves transformation by swapping x and y, which corresponds
 * to the rotation 90 degrees clockwise to get the the subcurve labeled 0
 *
 * position 3 involves a rotation by 90 degrees, then a reflection, hence we
 * swap and complement.
 *
 * Finally, after these transformations, we prepend new information to x,y
 * since we have just figured out which sub-quadrant of lower resolution we are
 * in.
 */


void hil_xy_from_s_ls(unsigned s, int n, unsigned *xp, unsigned *yp){

    int i,          // looping var
        sa, sb;     // we will be modifying s differently for the x and y coord

    unsigned x, y,  // coordinates we will build up to assign to *xp, *yp
             temp;  // temporary value to perform swaps

    for (i = 0; i< 2*n; i++){

        sa = (s >> (i + 1)) & 1;    // isolate the next two bits of s
        sa = (s >> i) & 1;

        if ((sa ^ sb) == 0){        // when sa and sb are the same, swap x, y
            temp = x;

            /* if sa = sb = 1, we also complement x and y.
             *      when sa = 0, y ^ 0 = y, so this is a simple swap
             *      when sb = 1, y ^ -1 will be the complement of 1, since
             *                       -1 is all 1s in twos-complement ints
             */
            x = y ^ (-sa);
            y = temp ^ (-sa);
        }

        /* now we prepend the new values to our accumulating coordinates.
         * we observe that we always prepend sa to the x coordinate,
         * and we always prepend (sa XOR sb) to the y coordinate.
         */
        x = (x >> 1)        // make room for new bit
          | (sa << 31);     // prepend sa in the new spot
        y = (y >> 1)
          | ((sa ^ xb) << 31);
    }

    /* set our return values, zero-pad for different lengths */
    *xp = x >> (32 - n);
    *yp = y >> (32 - n);
}
