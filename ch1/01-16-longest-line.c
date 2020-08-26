#include <stdio.h>

#define MAXLINE 10
#define TRUE 1
#define FALSE 0

int getline2(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
/* I struggled with this exercise. I wasn't making
    any progress until 1) I wrote down all possible 
    scenarios that needed to be solved 2) I wrote 
    down pseudo code and 3) I wrote a simple version
    first, made sure it solved one part of the
    problem correctly before improving it to address
    edge cases. The only function modified is main.

    Given maxline of 10, here are some input and 
    output scenarios for getline2:

    input   \n
    s[]     \n\0
    output  1
    
    input   12345678\n
    s[]     12345678\n\0
    output  9

    input   123456789012345\n
    s[]     123456789\0
    output  9
    
    input   123\nEOF
    s[]     123\n\0
    output  4

    Although maxline is 10, max length is 9 due to '\0'.
    I assume EOF is always preceded by '\n'.
    

    Pseudo-code:

    WHILE   there is another line
        IF      line is not actually complete
                add length to total line length
        ELSE
            IF  total line length not initialized
                set it to current line length
            IF  this is the last segment of a line continuation
                add length to total line length
            IF  total line length is max
                save line
                save total line length
            reset tracker
    print line and length */

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

void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}