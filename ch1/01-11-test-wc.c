#include <stdio.h>

#define IN 1    // inside a word
#define OUT 0   // outside a word

/* count lines, words, and characters in input */
/* What kinds of inputs are most likely to uncover bugs
    if there are any? */
/* Potential bugs:
    1. Cause integral overflow
    2. File with more than 65535 characters
    3. File with more than 65535 new lines 
    4. File with zero words */

main()
{
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}