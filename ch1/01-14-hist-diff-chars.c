#include <stdio.h>

#define UPPERLIMIT 127
#define LOWERLIMIT 33
#define NUMCHARS (UPPERLIMIT - LOWERLIMIT)

main()
{
    int c, i, j, ct, nwhite, nother;
    int nchar[NUMCHARS];
    
    ct = nwhite = nother = 0;
    for (i = 0; i < NUMCHARS; ++i) {
        nchar[i] = 0;
    }
    
    while ((c = getchar()) != EOF) {
        if (c >= LOWERLIMIT && c <= UPPERLIMIT) {
            ++nchar[c - LOWERLIMIT];
        } else if (c == ' ' || c == '\t' || c == '\n') {
            ++nwhite;
        } else {
            ++nother;
        }
    }

    for (i = 0; i < NUMCHARS; ++i) {
        if (ct < nchar[i]) {
            ct = nchar[i];
        }
    }
    if (ct < nwhite) {
        ct = nwhite;
    }
    if (ct < nother) {
        ct = nother;
    }
    
    printf("\nHistogram of different characters");
    for (i = ct; i > 0; --i) {
        printf("\n%6d |", i);
        for (j = 0; j < NUMCHARS; ++j) {
            if (i <= nchar[j]) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        if (i <= nwhite) {
            printf(" *");
        } else {
            printf("  ");
        }
        if (i <= nother) {
            printf(" *");
        } else {
            printf("  ");
        }
    }
    printf("\n%6c +", ' ');
    for (j = 0; j < NUMCHARS + 4; ++j) {
        printf("-");
    }
    printf("\n%6s :", "chars");
    for (i = 0; i < NUMCHARS; ++i) {
        printf("%c", i + LOWERLIMIT);
    }
    printf("\\s\\o\n");
}