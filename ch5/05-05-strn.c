#include <stdio.h>
#include <string.h>

void strncpy2(char *s, char *t, int n);
void strncat2(char *s, char *t, int n);
int strncmp2(char *s, char *t, int n);

int main()
{
    char s[100] = "green eggs and ham";
    char t[] = "green eggs";
    char *u = "green eggs and ham";
    char *v = "some green eggs and ham";

    printf("strncpy\n");
    printf("%s\n", s);
    strncpy2(s, t, 5);
    printf("%s\n", s);
    strncpy2(s, u, strlen(u));
    printf("%s\n", s);
    strncpy2(s, v, 0);
    printf("%s\n", s);

    printf("strncat\n");
    strncat2(s, t, 5);
    printf("%s\n", s);
    strncat2(s, u, strlen(u));
    printf("%s\n", s);
    strncat2(s, v, 0);
    printf("%s\n", s);
    
    printf("strncmp\n");
    printf("%s\n", s);
    printf("%s\t%d\n", t, strncmp2(s, t, 5));
    printf("%s\t%d\n", t, strncmp2(s, t, 15));
    printf("%s\t%d\n", t, strncmp2(s, t, 4));

    return 0;
}

void strncpy2(char *s, char *t, int n)
{
    int i;

    for (i=0; i < n && (*s++ = *t++); i++)
        ;
    *s = '\0';
}

void strncat2(char *s, char *t, int n)
{
    while (*s)
        s++;
    strncpy2(s, t, n);
}

int strncmp2(char *s, char *t, int n)
{
    int i;

    for (i=0; i < n  && (*t == *s); i++, s++, t++)
        ;
    return (i == n) ? 0 : *s - *t;
}