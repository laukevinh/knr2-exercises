#include <stdio.h>

#define swap(t,x,y) {t temp = (x); x = (y); (y) = temp;}
/* wrong */
/* #define swap(t,x,y) t temp = (x), x = (y), (y) = temp */
/* #define swap(t,x,y) {t temp = (x), x = (y), (y) = temp;} */

int main()
{
    int i, j;

    i = 1;
    j = 2;
    printf("%5d\t%5d\n", i, j);
    swap(int, i, j);
    printf("%5d\t%5d\n", i, j);

    return 0;
}