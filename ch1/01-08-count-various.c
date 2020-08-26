#include <stdio.h>

main()
{
    float ns, nt, nl;
    int c;

    ns = 0;
    nt = 0;
    nl = 0;

    while ((c = getchar()) != EOF){
        if (c == ' ') {
            ++ns;
        }
        if (c == '\t') {
            ++nt;
        }
        if (c == '\n') {
            ++nl;
        }
    }
    printf("Num spaces: %.0f\n", ns);
    printf("Num tabs: %.0f\n", nt);
    printf("Num newlines: %.0f\n", nl);
}