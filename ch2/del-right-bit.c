#include <stdio.h>

int main()
{
    unsigned x;

    x = 10;     // 1010
    printf("%5d ", x);
    x &= (x-1); // 1000
    printf("%5d", x);
    x &= (x-1); // 0000
    printf("%5d \n", x);

    return 0;
}