#include <stdio.h>

#define MAXLINE 1000

int strcmp2(char s[], char t[]);

int main()
{
    char s[MAXLINE] = "0123456789";
    char t[MAXLINE] = "abcdefghijklmnopqrstuvwxyz";
    char v[MAXLINE];
    int i, c;

    for (i=0, c='a'; c<='z'; i++, c++) {
        v[i] = c;
    }
    v[i] = '\0';

    printf("strcmp2(%s, %s)\n", s, s);
    printf("Actual Expected %d 1\n", strcmp2(s, s));
    printf("strcmp2(%s, %s)\n", s, t);
    printf("Actual Expected %d 0\n", strcmp2(s, t));
    printf("strcmp2(%s, %s)\n", t, v);
    printf("Actual Expected %d 1\n", strcmp2(t, v));
}

int strcmp2(char s[], char t[])
{
    int i;

    for (i=0; s[i]!='\0' && t[i]!='\0' && s[i]==t[i]; i++)
        ;
    if (s[i] == '\0' && t[i] == '\0')
        return 1;
    return 0;
}