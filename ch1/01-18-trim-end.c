#include <stdio.h>

#define MAXLINE 10
#define TRUE 1
#define FALSE 0
#define LINE_OVERFLOW 1
#define NORMAL 0

int getline2(char line[], int maxline);
void copy(char to[], char from[]);
int trim(char line[], int len);
int countblanks(char line[]);

/* K&R2 1-18 p31: Write a program to remove trailing blanks and tabs
   from each line of input, and to delete entirely blank lines. */
/* I didn't think I could solve this exercise without
    pointers, which K&R has yet to introduce. But Ben Pfaff
    outlined an approach below of "degrading gracefully", which
    gave me the hint needed to complete this exercise
    using only fixed sized arrays.

    "The program specification is ambiguous: does 'entirely blank lines'
    mean lines that contain no characters other than newline, or does
    it include lines composed of blanks and tabs followed by newline?
    The latter interpretation is taken here.

    This implementation does not use any features not introduced in the
    first chapter of K&R2.  As a result, it can't use pointers to
    dynamically allocate a buffer to store blanks that it has seen, so
    it must limit the number of blanks that are allowed to occur
    consecutively.  (This is the value of MAXQUEUE, minus one.)

    It is intended that this implementation 'degrades gracefully.'
    Even though a particular input might have 1000 or more blanks or
    tabs in a row, causing a problem for a single pass, multiple passes
    through the file will correct the problem.  The program signals the
    need for such an additional pass by returning a failure code to the
    operating system.  (EXIT_FAILURE isn't mentioned in the first
    chapter of K&R, but I'm making an exception here.)" */

main ()
{
    int len;
    int allblanks, getmore;
    int exit_code;
    char line[MAXLINE];
    char prevline[MAXLINE];
    char prev2line[MAXLINE];

    allblanks = TRUE;
    getmore = FALSE;
    exit_code = NORMAL;

    while ((len = getline2(line, MAXLINE)) > 0) {
        if (line[len-1] == '\n') {
            len = trim(line, len);
            if (getmore == TRUE) {
                if (len == 1) {
                    if (allblanks == TRUE) {
                        prevline[MAXLINE-2] = '\n';
                    } else {
                        trim(prevline, MAXLINE);
                    }
                    exit_code = LINE_OVERFLOW;
                }
                printf("%s", prevline);
            }
            if (len > 1) {
                printf("%s", line);
            }
            allblanks = TRUE;
            getmore = FALSE;
        } else {
            if (allblanks = TRUE && countblanks(line) != MAXLINE-1) {
                allblanks = FALSE;
            }
            if (getmore == TRUE) {
                copy(prev2line, prevline);
                printf("%s", prev2line);
            }
            copy(prevline, line);
            getmore = TRUE;
        }
    }
    // in case file doesn't end with '\n'
    if (line[len-1] != '\n') {
        if (getmore == TRUE) {
            printf("%s", prevline);
        }
        printf("%s", line);
    }
    
    return exit_code;
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

/* Removes adjacent spaces or tabs at end of line.
    Leaves at least '\n'. Returns new length. */
int trim(char s[], int len)
{
    int i;

    for (i=len-2; i>=0 && (s[i]==' ' || s[i]=='\t'); --i) {
        ;
    }
    ++i;
    s[i] = '\n';
    ++i;
    s[i] = '\0';

    return i;
}

/* Counts number of blanks and tabs. Ignores '\n' */
int countblanks(char s[])
{
    int nblanks = 0;

    for (int i=0; i<MAXLINE; i++) {
        if (s[i] == ' ' || s[i] == '\t') {
            ++nblanks;
        }
    }

    return nblanks;
}