#include <stdio.h>

#define MAXLINE 10

int getline2(char line[], int maxline);
void reverse(char s[]);

/* print longest input line */

main ()
{
    int len;
    char line[MAXLINE];

    while ((len = getline2(line, MAXLINE)) > 0) {
        if (len > 1) {
            reverse(line);
            printf("%s", line);
        }
    }
    
    return 0;
}

int getline2(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void reverse(char s[])
{
    int i, j;
    char c;

    for (i=0; i<MAXLINE && s[i] != '\0'; i++) {
        ;
    }
    --i;
    if (s[i] == '\n') {
        s[i] == '\0';
        --i;
    }
    for (j=0; j<i/2+1; j++) {
        c = s[j];
        s[j] = s[i-j];
        s[i-j] = c;
    }
}