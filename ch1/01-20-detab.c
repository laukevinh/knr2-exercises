#include <stdio.h>

main()
{
    int c, i, j, nspaces, tablen;

    i = 0;
    tablen = 4;

    while ((c = getchar()) != EOF) {
        ++i;
        if (c == '\t') {
            nspaces = tablen - ((i - 1) % tablen);
            for (j=0; j<nspaces; j++) {
                putchar(' ');
            }
            i = 0;
        } else {
            putchar(c);
        }
        if (c == '\n') {
            i = 0;
        }
    }

    return 0;
}