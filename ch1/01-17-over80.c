#include <stdio.h>

#define MAXLINE 20    /* maximum input line size */
#define TRUE 1
#define FALSE 0
#define THRESHOLD 10

int getline2(char line[], int maxline);

/* print all input lines >80 characters */
/* I've modified the theshold to 10 so we can test.
    This time I wrote out the pseudo code first, which
    helped me produce a working program quicker than
    diving directly into the code. This program only
    modified main. Copy function was removed.
    
    WHILE there are more lines
        IF      line is complete and ends with \n
            IF  this is the last part of a longer line or 
            IF  this len > threshold
                print line
            reset getmore flag
        ELSE
            IF  this line reached the maxlength
                print line
                getmore flag = True */

main ()
{
    int len;
    int getmore;
    char line[MAXLINE];

    getmore = FALSE;

    while ((len = getline2(line, MAXLINE)) > 0) {
        if (line[len-1] == '\n') {
            if (getmore == TRUE || len > THRESHOLD) {
                printf("%s", line);
            }
            getmore = FALSE;
        } else if (len == MAXLINE-1) {
            printf("%s", line);
            getmore = TRUE;
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