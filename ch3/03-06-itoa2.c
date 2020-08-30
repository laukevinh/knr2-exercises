#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXLINE 1000

void reverse(char s[]);
void itoa(int n, char s[], int pad);

int main()
{
    char s[MAXLINE];
    int i;

    printf("         |         |\n");
    i = 1234567890;
    itoa(i ,s, 20);
    printf("%s|\n", s);

    return 0;
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

void itoa(int n, char s[], int pad)
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
    while (i < pad)
        s[i++] = ' ';
    s[i] = '\0';
    reverse(s);
}