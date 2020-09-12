#include <stdio.h>

#define MAXNUM 20
int main()
{
    int i, testn, n[MAXNUM];

    testn = 8;
    for (i = 0; i < MAXNUM; i++)
        n[i] = i;
    for (i = 0; i < MAXNUM; i++) {
        if (n[i] == testn) {
            printf("break at %d\n", n[i]);
            break;
        }
        printf("%d ", n[i]);
    }
    i = 0;
    while (i < MAXNUM) {
        if (n[i] == testn) {
            printf("break at %d\n", n[i]);
            break;
        }
        printf("%d ", n[i]);
        i++;
    }
    return 0;
}