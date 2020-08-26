#include <stdio.h>

#define MAXLINE 10
#define TRUE 1
#define FALSE 0

int getline2(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
/* Rewrite for loop in getline2 without using && or || */

main ()
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

int getline2(char s[], int lim)
{
    int c, i, stop;

    /* write loop equivalent to for loop below without && or ||

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }

    */

    i=0;
    stop = FALSE;
    while (!stop) {
        if (i>=lim-1) {
            stop = TRUE;
        } else if ((c=getchar())=='\n') {
            stop = TRUE;
        } else if (c==EOF) {
            stop = TRUE;
        } else {
            s[i] = c;
            ++i;
        }
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
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
