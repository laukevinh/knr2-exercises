#include <stdio.h>

#define MAXLINE 1000

/* compile with `gcc 04-01-strrindex.c getline2.c strindex.c */

int getline2(char line[], int max);
int strindex(char source[], char searchfor[]);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ea";

int main()
{
    char line[MAXLINE];
    int found, idx;
    idx = -1;
    found = 0;

    while (getline2(line, MAXLINE) > 0) {
        if ((idx = strindex(line, pattern)) >= 0) {
            printf("L%3d\t%s", idx, line);
            found++;
        }
        if ((idx = strrindex(line, pattern)) >= 0) {
            printf("R%3d\t%s", idx, line);
        }
    }
    return found;
}

int strrindex(char s[], char t[])
{
    int i, j, k, idx;

    idx = -1;

    for (i = 0; s[i] != '\0'; i++) {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            idx = i;
    }
    return idx;
}