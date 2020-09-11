#include <stdio.h>

void strcat2(char *s, char *t);

int main()
{
    char s[100] = "original ";
    char t[] = "stuff to copy";
    char *v = " pointer stuff.";

    strcat2(s, t);
    printf("%s\n", s);
    strcat2(s, v);
    printf("%s\n", s);
    return 0;
}

void strcat2(char *s, char *t)
{
    while (*s)
        s++;
    while (*s++ = *t++)
        ;
}