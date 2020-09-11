#include <stdio.h>

#define MAXLINE 10
#define TRUE 1
#define FALSE 0

int getline2(char *line, int maxline);
void copy(char to[], char from[]);

/* KnR Exercise 05-06   Rewrite appropriate programs from
    earlier chapters and exercises with pointers instead of
    array indexing. This file rewrites getline2 from 
    exercise 01-16. Note that repriting of Longest line
    is limited to size of MAXLINE. */

int main ()
{
    int len, tlen, max;
    int getmore;
    char line[MAXLINE];
    char longest[MAXLINE];
    char temp[MAXLINE];

    tlen = 0;
    max = 0;
    getmore = FALSE;

    while ((len = getline2(line, MAXLINE)) > 0) {
        if ((len == MAXLINE-1 && line[len-1] != '\n')){
            if (getmore == FALSE) {
                copy(temp, line);
                getmore = TRUE;
            }
            tlen = tlen + len;
        } else {
            if (tlen == 0) {
                tlen = len;
            } else if (tlen >= MAXLINE-1) {
                tlen = tlen + len;
            }
            if (tlen > max) {
                max = tlen;
                if (getmore == TRUE) {
                    copy(longest, temp);
                    longest[MAXLINE - 2] = '\n';
                    getmore = FALSE;
                } else {
                    copy(longest, line);
                }
            }
            tlen = 0;
        }
    }
    
    if (max > 0) {
        printf("%s\n", longest);
        printf("len = %d\n", max);
    }
    return 0;
}

int getline2(char *s, int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        *s++ = c;
    }
    if (c == '\n') {
        *s++ = c;
        ++i;
    }
    *s = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}