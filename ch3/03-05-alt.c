#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void reverse(char s[]);
int convert(int c);
void itob(int n, char s[], int b);

/* Sure enough, there's a much more straightforward
    method. Just replace 10 with `base` in the existing
    code and it works. */

int main()
{
    char s[MAXLINE];
    int i, b;

    i = 6;
    b = 2;
    itob(i ,s, b);
    printf("%10d%10d\t%10s\n", i, b, s);

    i = 63;
    b = 8;
    itob(i ,s, b);
    printf("%10d%10d\t%10s\n", i, b, s);

    i = 1000000;
    b = 16;
    itob(i ,s, b);
    printf("%10d%10d\t%10s\n", i, b, s);

    i = 256;
    for (b = 2; b <= 16; b *= 2) {
        itob(i ,s, b);
        printf("%10d%10d\t%10s\n", i, b, s);
    }
    
    i = 310;
    for (b = 2; b <= 16; b *= 2) {
        itob(i ,s, b);
        printf("%10d%10d\t%10s\n", i, b, s);
    }

    return 0;
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

int convert(int c)
{
    if (c < 0 || c > 35) {
        return '#';
    } else if (c > 9) {
        return c + 'A' - 10;
    } else {
        return c + '0';
    }
}

void itob(int n, char s[], int b)
{
    int i, sign;
    char CONVERT[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    i = 0;
    if ((sign = n) < 0) {
        s[i++] = CONVERT[((-(n+1) % b) + 1) % b];
        n /= 10;
        n = -n;
    }
    do {
        s[i++] = CONVERT[n % b];
    } while ((n /= b) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}