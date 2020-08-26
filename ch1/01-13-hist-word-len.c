#include <stdio.h>

#define IN  1
#define OUT 0
#define MAXLEN 10

main()
{
    int c, i, nc, state;
    int wordlen[MAXLEN];

    state = OUT;
    nc = 0;
    for (i = 0; i < MAXLEN; ++i) {
        wordlen[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == IN) {
                ++wordlen[nc];
                state = OUT;
                nc = 0;
            }
        } else {
            state = IN;
            if (nc < MAXLEN - 1) {
                ++nc;
            }
        }
    }

    printf("Histogram of word lengths\n\n");
    printf("%3s %3s\n", "BIN", "Ct");
    for (i = 1; i < MAXLEN; ++i) {
        if (i == MAXLEN - 1) {
            printf(">%2d %3d ", i-1, wordlen[i]);
        } else {
            printf("%3d %3d ", i, wordlen[i]);
        }
        for (int j = 0; j < wordlen[i]; ++j) {
            printf(".");
        }
        printf("\n");
    }
}