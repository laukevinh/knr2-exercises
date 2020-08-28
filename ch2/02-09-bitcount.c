#include <stdio.h>

int bitcount(unsigned x);

/* Subtracting 1 will always flip the rightmost bit.
    If the rightmost bit is 1, it turns to 0.
    If the rightmost bit is 0, it turns to 1.

    The cool feature with flipping 0 to 1 is that the 
    adjacent zeros will turn to 1 due to carry over.
    For example, if
        x == 1000
    and
        x-1 == 0111
    then
        x & (x-1) == 0000
        
    Count the number of times needed to x &= (x-1)
    until x == 0. That count is equal to the number 
    of 1 bits. */

int main()
{
    unsigned x;

    x = 10;     // 1010
    printf("%5d bitcount %5d\n", x, bitcount(x));
    x = 128;    // 1000 0000
    printf("%5d bitcount %5d\n", x, bitcount(x));
    x = 127;    // 0111 1111
    printf("%5d bitcount %5d\n", x, bitcount(x));
    x = 169;      // 1010 1010
    printf("%5d bitcount %5d\n", x, bitcount(x));
    return 0;
}

int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x &= x-1, b++) {
        ;
    }
    return b;
}