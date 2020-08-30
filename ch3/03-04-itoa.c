#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXLINE 1000

void reverse(char s[]);
void itoa(int n, char s[]);

/* Signed numbers range from -x to x-1, since
    0 takes up one of the representations for
    the positive digits. Thus, the largest negative
    number would overflow if flipped to positive.
    
    If n is the largest negative number, then 
    decrease by 1 before flipping to positive.
    perform the same routine and fix the 1's
    position at the end of the routine. */

int main()
{
    char s[MAXLINE];
    int i;

    i = 1234567890;
    itoa(i ,s);
    printf("%40d\t%s\n", i, s);

    i = -1234567890;
    itoa(i ,s);
    printf("%40d\t%s\n", i, s);

    i = (1 << 31) - 1;
    itoa(i ,s);
    printf("%40d\t%s\n", i, s);

    i = -(1 << 31);
    itoa(i ,s);
    printf("%40d\t%s\n", i, s);

    return 0;
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, j, sign, maxneg, carry;
    enum boolean { FALSE, TRUE };
    
    maxneg = FALSE;
    if ((sign = n) < 0) {
        if (n == INT_MIN) {
            n = -(n+1);
            maxneg = TRUE;
        } else {
            n = -n;
        }
    }
    i = j = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (maxneg) {
        j = 0;
        carry = FALSE;
        do {
            if (s[j] == '9') {
                s[j++] = '0';
                carry = TRUE;
            } else if (s[j]>='0' && s[j]<='9') {
                s[j++] = s[j] + 1;
            } else {
                s[j++] = '1';
            }
        } while (carry == TRUE);
    }
    i = (j > i) ? j : i;
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}