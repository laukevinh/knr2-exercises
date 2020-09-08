/* KnR Exercise 05-07   Rewrite readlines to store lines 
    in an array supplied by main , rather than calling 
    alloc to maintain storage. How much faster is the 
    program?

    I wasn't sure how to start, so took a peek at solutions
    in clc-wiki. The gist is to provide a big array to
    readlines which, in addition to reading all input,
    will use pointer arithmetic to maintain enough space to 
    store lines. Getting storage space for the next line is
     simple: check that buffer remaining is >= len. */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */
#define MAXBUF  10000

char *lineptr[MAXLINES];

int readlines2(char *lineptr[], int nlines, char linebuf[]);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main()
{
    int nlines;     /* number of input lines read */
    char linebuf[MAXBUF];
    
    if ((nlines = readlines2(lineptr, MAXLINES, linebuf)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000     /* max length of any input line */
int getline2(char *, int);

int readlines2(char *lineptr[], int maxlines, char linebuf[])
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    p = linebuf;
    while ((len = getline2(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || linebuf + MAXBUF - p < len)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)      /* do nothing if array contains */
        return;             /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int getline2(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}