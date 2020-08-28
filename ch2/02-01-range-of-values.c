#include <stdio.h>
#include <limits.h>
#include <float.h>



int main(void)
{
    char c;
    short sh;
    int i, n;
    long ln;

    printf("char\n");
    for (n=1, c=2; c!=0; n++, c=c*2) {
        printf("%6d ", c);
    }
    printf("n=%d\n", n);
    for (n=1, c=-2; c!=0; n++, c=c*2) {
        printf("%6d ", c);
    }
    printf("n=%d\n", n);

    printf("short\n");
    for (n=1, sh=2; sh!=0; n++, sh*=2) {
        printf("%6d ", sh);
    }
    printf("n=%d\n", n);
    for (n=1, sh=-2; sh!=0; n++, sh*=2) {
        printf("%6d ", sh);
    }
    printf("n=%d\n", n);
    
    printf("int\n");
    for (n=1, i=2; i!=0; n++, i*=2) {
        printf("%12d ", i);
    }
    printf("n=%d\n", n);
    for (n=1, i=-2; i!=0; n++, i*=2) {
        printf("%12d ", i);
    }
    printf("n=%d\n", n);

    printf("long\n");
    for (n=1, ln=2; ln!=0; n++, ln*=2) {
        printf("%12ld ", ln);
    }
    printf("n=%d\n", n);
    for (n=1, ln=-2; ln!=0; n++, ln*=2) {
        printf("%12ld ", ln);
    }
    printf("n=%d\n", n);

    return 0;
}