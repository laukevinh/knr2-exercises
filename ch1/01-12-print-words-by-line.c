#include <stdio.h>

#define IN  1 // in char sequence more than 1 space long
#define OUT 0

/* output words by line */

main()
{
    int c, state;

    state = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t') {
            if (state == OUT) {
                putchar('\n');
                state = IN;
            }
        } else {
            putchar(c);
            state = OUT;
        }
    }
}