#include <stdio.h>

main()
{
    double nc;

    for (nc = 0; getchar() != EOF; ++nc) {
        ;
    }
    printf("char count: %.0f\n", nc);
}