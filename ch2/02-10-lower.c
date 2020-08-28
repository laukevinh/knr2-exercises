#include <stdio.h>

int lower(int c);

int main()
{
    char c;

    c = 'T';
    printf("%c %c\n", c, lower(c));
    c = 'Z';
    printf("%c %c\n", c, lower(c));
    c = 's';
    printf("%c %c\n", c, lower(c));
    c = ' ';
    printf("%c %c\n", c, lower(c));
    c = '\t';
    printf("%c %c\n", c, lower(c));
    c = '4';
    printf("%c %c\n", c, lower(c));
    c = 'A';
    printf("%c %c\n", c, lower(c));
    c = 'z';
    printf("%c %c\n", c, lower(c));

    return 0;
}

int lower(int c)
{
    return (c>='A' && c<='Z') ? (c+'a'-'A') : c;
}