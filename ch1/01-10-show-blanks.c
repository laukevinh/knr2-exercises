#include <stdio.h>

main()
{
    int c, d;
    while ((c = getchar()) != EOF) {
        d = 0;
        if (c == '\t') {
            putchar('\\');
            putchar('t');
            d = 1;
        }
        if (c == '\b') {
            putchar('\\');
            putchar('b');
            d = 1;
        }
        if (c == '\\') {
            putchar('\\');
            putchar('\\');
            d = 1;
        }
        if (d == 0) {
            putchar(c);
        }
    }
}