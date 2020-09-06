#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

int main()
{
    char s[100] = "green eggs and ham";
    char t[] = "green eggs";
    char *u = "green eggs and ham";
    char *v = "some green eggs and ham";

    printf("%s\n", s);
    printf("%s\t%d\n", t, strend(s, t));
    printf("%s\t%d\n", u, strend(s, u));
    printf("%s\t%d\n", v, strend(s, v));
    return 0;
}

int strend(char *s, char *t)
{
    int ns, nt, diff;

    diff = strlen(s) - strlen(t);
    if (diff < 0)
        return 0;
    s += diff;
    while (*s && *s++ == *t++)
        ;
    return (*s) ? 0 : 1;
}