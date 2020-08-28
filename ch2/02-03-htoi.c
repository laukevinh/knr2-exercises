#include <stdio.h>

int htoi(char s[]);
int lower(int c);
int convert(int c);

int main()
{
    char s1[] = "0x1AE8C";
    char s2[] = "0000000";
    char s3[] = "0x3F";
    char s4[] = "0x40";
    char s5[] = "0x7E";
    char s6[] = "FFF";
    char s7[] = "F";
    char s8[] = "";

    printf("%20s = %30d\n", s1, htoi(s1));
    printf("%20s = %30d\n", s2, htoi(s2));
    printf("%20s = %30d\n", s3, htoi(s3));
    printf("%20s = %30d\n", s4, htoi(s4));
    printf("%20s = %30d\n", s5, htoi(s5));
    printf("%20s = %30d\n", s6, htoi(s6));
    printf("%20s = %30d\n", s7, htoi(s7));
    printf("%20s = %30d\n", s8, htoi(s8));
    return 0;
}

int htoi(char s[])
{
    int n, i, c;
    int stop, check;
    enum boolean { FALSE, TRUE };

    if (s[0] == '0' && lower(s[1]) == 'x') {
        i = 2;
    } else {
        i = 0;
    }
    stop = FALSE;
    n = 0;
    while (!stop) {
        c = lower(s[i]);
        if ((c>='0' && c<='9') || (c>='a' && c<='f')) {
            n = 16 * n + convert(c);
            i++;
        } else {
            stop = TRUE;
        }
    }

    return n;
}

int lower(int c)
{
    if (c>='A' && c<='Z') {
        return c + 'a' - 'A';
    } else {
        return c;
    }
}

int convert(int c)
{
    if (c>='a' && c<='f') {
        return c - 'a' + 10;
    } else if (c>='0' && c <='9') {
        return c - '0';
    }
}