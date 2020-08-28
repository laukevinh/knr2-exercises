#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

/* pseudocode
    get the leftmost bits from x
    make enough zeros for the n bits from y
    overwrite the zeros with the n bits from y 
    make enough zeros for the remaining right bits in x
    overwrite the zeros with the remaining right bits from x */

int main()
{
    unsigned x, y, z;
    int n, p;
    x = 155;    // 1001 1011
    y = 7;      // 0000 0111
    z = 69;     // 0100 0101
    n = 3;
    p = 4;

    printf("setbits(%d, %d, %d, %d) ", x, p, n, y);
    printf("== %d\n", setbits(x, p, n, y)); // 1001 1111 = 159

    printf("setbits(%d, %d, %d, %d) ", x, p, n, z);
    printf("== %d\n", setbits(x, p, n, z)); // 1001 0111 = 151

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