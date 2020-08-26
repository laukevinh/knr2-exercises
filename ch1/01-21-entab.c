#include <stdio.h>

#define TRUE 1
#define FALSE 0

main()
{
    int c, i, offset, ncol, nspace, tablen;

    i, offset, ncol, nspace = 0;
    tablen = 4;

    while ((c = getchar()) != EOF) {
        ++ncol;
        if ((ncol-1)%tablen == 0 && nspace > 0) {
            if (nspace > 1) {
                putchar('\t');
            }
            nspace = 0;
        }
        if (c == '\t') {
            offset = tablen - ((ncol-1) % tablen);
            nspace += offset;
            ncol += offset - 1;
        } else if (c == ' ') {
            ++nspace;
        } else {
            for (i=0; i<nspace; i++) {
                putchar(' ');
            }
            putchar(c);
            nspace = 0;
            if (c == '\n') {
                ncol = 0;
            }
        }
    }

    return 0;
}