#define LOOKUP_BIT_I(x,i)       ((x >> i) & 1)

#define APPEND_TO_S_COLUMN      0x361E9CB4
#define S_LOOKUP(row)           ((APPEND_TO_S_COLUMN >> 2 * row) & 3)

/* this is an encoding of the transitition table that, given our current
 * row, looks up the next state we have to go to, and isolates those
 * 2 bits that uniquely define that state
 */
#define STATE_TRANSITION_COLUMN 0x8FE65831
#define STATE_LOOKUP(row)       ((STATE_TRANSITION_COLUMN >> 2 * row) & 3)

unsigned hil_s_from_xy(unsigned x, unsigned y, int n){

    int i;
    unsigned state, s, row;

    state = 0;
    s = 0;

    for(i = n-1; i >= 0; i--){
        /* we will determine which quadrant of states we are in by
         * the number of state we are in.  The first 4*state operation
         * gets us exactly to the 0th element of our list of rows associated
         * with the given state.
         *
         * Then we need to modify the 2 least significant bits to select
         * which of the 4 rows we are in associated with our state.
         * We use the X bit to modify the second to last bit, and the
         * Y bit to modify the last bit.
         *
         * This is simply how the transition table has been defined. (that x
         * impacts the most signnificant bit of the substate row), in
         * table 16-5.
         */
        row = (4*state)                 // since there are 4 rows per state
            | (2*(LOOKUP_BIT_I(x,i)))
            | (LOOKUP_BIT_I(y,i));

        s = (s << 2)            // make room for the new bits we are adding
          | S_LOOKUP(row);      // look up the bits in the table, append them


        state = STATE_LOOKUP(row);  // lookup the new state based on curr row
    }

    return s;
}
