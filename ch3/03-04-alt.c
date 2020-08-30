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
    
    This is an alternate version from clc-wiki.
    It's simpler than mine because it doesn't deal
    with carry overs. It subtracts 1, flips to
    positive before performing the modulo, then
    add back one. This secures the first digit.
    The original n is divided by 10 then flipped
    to positive, which will be within the max
    positive value. The rest of the program is
    the same as KnR.  */

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
    int i, j, sign;

    i = 0;
    if ((sign = n) < 0) {
        s[i++] = ((-(n+1) % 10) + 1) % 10 + '0';
        n /= 10;
        n = -n;
    }
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}