#include <stdio.h>

#define SIZE   10

float getfloat(float *pn);

/* KnR Exercise 05-02   Write getfloat , the floating-point 
    analog of getint . What type does getfloat return as its
    function value?
    
    Made changes to main so that array would only fill up if 
    n was a digit. Otherwise it continues to read. 

    Also commented out first ungetch in getfloat to avoid 
    immediately exiting program upon seeing something
    like a letter. 
    
    Program won't recognize decimal without leading digit.
    '.001' is wrong. '0.001' is acceptable. */

int main()
{
    int n, i;
    float m, array[SIZE], getfloat(float *);

    for (n=0, i=0; n < SIZE && (m = getfloat(&array[i])) != EOF; n++)
        if (m > 0)
            i++;
    for (n=0; n < i; n++)
        printf("%f ", array[n]);
    return 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getfloat: get next integer from input into *pn */
float getfloat(float *pn)
{
    int c, sign;
    float power;

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
    if (c == '.') {
        power = 1.0;
        while (isdigit(c = getch())) {
            power *= 10.0;
            *pn = 10 * *pn + (c - '0');
        }
        *pn /= power;
    }
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