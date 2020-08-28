#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);

/* pseudocode
    let y be invert of x
    right shift y so that the position of n bits are against the right
    use setbits on x and y */

int main()
{
    unsigned x, y, z;
    int n, p;
    x = 155;    // 1001 1011
    y = 7;      // 0000 0111
    z = 69;     // 0100 0101
    n = 3;
    p = 4;

    printf("invert(%d, %d, %d) ", x, p, n);
    printf("== %d\n", invert(x, p, n)); // 1000 0111 = 135

    printf("invert(%d, %d, %d) ", y, p, n);
    printf("== %d\n", invert(y, p, n)); // 0001 1011 = 27

    printf("invert(%d, %d, %d) ", z, p, n);
    printf("== %d\n", invert(z, p, n)); // 0101 1001 = 89

    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned z;

    z = x >> (p+1);
    z = z << n;
    z = z | (y & ~(~0<<n));
    z = z << (p+1-n);
    z = z | (x & ~(~0 << (p+1-n)));
    return z;
}

unsigned invert(unsigned x, int p, int n)
{
    unsigned y;

    y = ~x >> (p+1-n);
    return setbits(x, p, n, y);
}