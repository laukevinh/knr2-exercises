#include <stdio.h>

int main()
{
    unsigned x, y;

    x = 2;
    y = 5;

    printf("%4d flip %4d\n", x, ~x);
    printf("%4d flip %4d\n", y, ~y);
    printf("%4d flip %4d\n", 0U, ~0U);
    printf("%4d flip %4d\n", 077U, ~077U);

    return 0;
}