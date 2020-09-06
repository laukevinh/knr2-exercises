#include <stdio.h>

#define SIZE   10

int getint(int *pn);

/* KnR Exercise 05-01   As written, getint treats a + or - 
    not followed by a digit as a valid representation of zero. 
    Fix it to push such a character back on the input.
    
    Made changes to main so that array would only fill up if 
    n was a digit. Otherwise it continues to read. 

    Also commented out first ungetch in getint to avoid 
    immediately exiting program upon seeing something
    like a letter. */

int main()
{
    int n, m, i, j, array[SIZE], getint(int *);

    for (n=0, i=0; n < SIZE && (m = getint(&array[i])) != EOF; n++)
        if (m > 0)
            i++;
    for (n=0; n < i; n++)
        printf("%d ", array[n]);
    return 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))    /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        /* ungetch(c); */     /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            ungetch(c);
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}