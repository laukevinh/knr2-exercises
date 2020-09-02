#include <stdio.h>

int main()
{
    char c = EOF;

    printf("1 == 1\t\t%d\n", 1 == 1);
    printf("EOF == -1\t%d\n", EOF == -1);
    printf("%c == EOF\t%d\n", c, c == EOF);
    return 0;
}