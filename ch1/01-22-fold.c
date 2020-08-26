#include <stdio.h>

#define MAXLINE 20

int getline2(char line[], int maxline);
int append(char to[], char from[], int start, int end);

/* take input and print it out with folds at spaces */
/* Pseudocode
    While   there is a new line
        add new line to the end of fold line
        IF  fold line ends in \n
            print entire fold line
        ELSE
            find the position of the last blank in fold line
            IF  fold line doesn't have blanks
                print entire fold line
                print \n
            ELSE
                print up to the blank
                print \n
                shift remaining text in fold line to front of array */

int main ()
{
    int i, pos, buffersize, len, foldlen;
    char line[MAXLINE];
    char fold[MAXLINE];

    foldlen = 0;
    buffersize = MAXLINE;

    while ((len = getline2(line, buffersize)) > 0) {
        foldlen = append(fold, line, foldlen, foldlen + len);
        if (fold[foldlen-1] == '\n') {
            printf("%s", fold);
            foldlen = 0;
        } else {
            for (pos=foldlen; pos>=0 && fold[pos]!=' '; pos--) {
                ;
            }
            if (pos < 0) {
                printf("%s\n", fold);
                foldlen = 0;
            } else {
                ++pos;
                for (i=0; i<pos; i++) {
                    putchar(fold[i]);
                }
                printf("\n");
                for (i=0; pos<foldlen; pos++, i++) {
                    fold[i] = fold[pos];
                }
                fold[i] = '\0';
                foldlen = i;
            }
        }
        buffersize = MAXLINE - foldlen;
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

int append(char to[], char from[], int startpos, int endpos)
{
    int i;

    for (i=startpos; i<endpos+1; i++) {
        to[i] = from[i-startpos];
    }
    return endpos;
}