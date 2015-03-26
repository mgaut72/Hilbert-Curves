#define LOOKUP_BIT_I(x,i)       ((x >> i) & 1)

unsigned hil_s_from_xy_ls(unsigned x, unsigned y, int n){

    int i,              // current iteration over coordinate bits
        xi,             // the ith bit of the x coordinate
        yi;             // ith bit of the y coordinate

    unsigned s,         // distance along the curve
             temp;      // temp var for swap/complementing

    s = 0;

    for (i = n - 1; i >= 0; i--) {

        // isolate the ith bits of (x,y)
        xi = LOOKUP_BIT_I(x,i);
        yi = LOOKUP_BIT_I(y,i);

        /* according to the lam-shapiro method, when y_i == 1, we don't
         * swap or compliment, since this corresponds to a sub-curve
         * that is already properly oriented (either 1 or 2 in the diagram)
         *
         *                ┌──┐   ┌──┐
         *                │1 │   │ 2│
         *                │  └───┘  │
         *                │         │
         *                └──┐   ┌──┘
         *                 0 │   │ 3
         *                ───┘   └──
         */
        if (yi == 0) {

            temp = x;

            /* if xi = 1, then we also need to complement
             *      when xi = 0, y ^ 0 = y, so this is a simple swap
             *      when xi = 1, y ^ -1 will be the complement of 1, since
             *                       -1 is all 1s in twos-complement ints
             */
            x = y ^ (-xi);
            y = temp ^ (-xi);
        }

        /* Append two bits to s.
         *
         * see transition table
         *
         *      4 * s is a shift by two bits
         *      2 * xi gets the xi bit into the 2nd position that just opened
         *      (xi ^ yi) is the append value for the least sig. bit
         *              see the table in hacker's delight
         */
        s = 4*s + 2*xi + (xi^yi);

    }
    return s;
}
