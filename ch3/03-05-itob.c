#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void reverse(char s[]);
int convert(int c);
void itob(int n, char s[], int b);

/* This one was tough. My psuedocode didn't address
    enough scenarios so I ended fixing many bugs
    after typing it out. I brushed up my gdb skills.
    
    Find b^i <= n < b^(i+1) i.e. largest multiple of b
    Record n / b^i in s[i]
    let n = remainder of n / b^i
    Repeat above steps until b > n
    Record the remainder in the 1s slot
    
    Example: n = 310, base = 4
    4^4 <= n < 4^5
    Start with slot s[4], the 256s place, which fits 310 / 256 = 1.
    Remainder n=54.
    Next slot s[3], the 64s place, fits 54 / 64 = 0.
    Next slot s[2], the 16s place, fits 54 / 16 = 3.
    Remainder n=6.
    Next slot s[1], the  4s place, fits  6 /  4 = 1.
    Remainder n=2.
    Next slot s[0], the  1s place, fits the remainder 2.
    Result is '21301', which is reversed to give '10312'. */

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
    int i, multi;

    for (i = 0, multi = b; multi <= n; i++, multi *= b) {
        ;
    }
    s[i+1] = '\0';
    multi /= b;

    while (b <= n) {
        if (multi <= n) {
            s[i--] = convert(n / multi);
            n %= multi;
        } else {
            s[i--] = '0';
        }
        multi /= b;
    }
    while (i > 0) {
        s[i--] = '0';
    }
    s[i] = convert(n);
    reverse(s);
}