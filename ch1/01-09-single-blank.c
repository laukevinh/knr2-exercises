#include <stdio.h>

main()
{
    int c, ns;

    ns = 0;
    while ((c = getchar()) != EOF) {
        if (c != ' ') {
            ns = 0;
        }
        if (ns == 0) {
            putchar(c);
            if (c == ' ') {
                ++ns;
            }
        }
    }
}