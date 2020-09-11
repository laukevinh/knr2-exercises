#include <stdio.h>

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
    int ns, nt;

    ns = nt = 0;
    while (*s) {
        s++;
        ns++;
    }
    while (*t) {
        t++;
        nt++;
    }
    if (nt > ns)
        return 0;
    while (nt > 0) {
        if (*--s != *--t)
            return 0;
        --nt;
    }
    return 1;
}