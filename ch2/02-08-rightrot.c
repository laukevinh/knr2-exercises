#include <stdio.h>

unsigned rightrot(unsigned x, int n);

/* pseudocode
    let y be right n bits of x
    right shift x by n bits
    count remaining bits in x after shift
    left shift y by count 
    combine x and y using OR */

int main()
{
    unsigned x, y, z;
    int n;
    x = 155;    // 1001 1011
    y = 7;      // 0000 0111
    z = 69;     // 0100 0101
    n = 3;

    printf("rightrot(%d, %d) ", x, n);
    printf("== %d\n", rightrot(x, n)); // 0111 0011 = 115

    printf("rightrot(%d, %d) ", y, n);
    printf("== %d\n", rightrot(y, n)); // 0000 0111 = 7

    printf("rightrot(%d, %d) ", z, n);
    printf("== %d\n", rightrot(z, n)); // 0101 1000 = 88

    return 0;
}

unsigned rightrot(unsigned x, int n)
{
    unsigned leftbits, rightbits;
    int i;

    rightbits = x & ~(~0 << n);
    x = x >> n;
    for (i = 0, leftbits = x; leftbits > 0; i++) {
        leftbits = leftbits >> 1;
    }
    return x | (rightbits << i);
}