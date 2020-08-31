#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

int main()
{
    double atof(char []);
    char s1[] = "123.45e-6";
    char s2[] = "1.2345E6";
    char s3[] = "1.2";
    char s4[] = "1.";
    char s5[] = ".12";
    char s6[] = "0.9";
    char s7[] = "10.0";

    printf("%10s\t%f\n", s1, atof(s1));
    printf("%10s\t%f\n", s2, atof(s2));
    printf("%10s\t%f\n", s3, atof(s3));
    printf("%10s\t%f\n", s4, atof(s4));
    printf("%10s\t%f\n", s5, atof(s5));
    printf("%10s\t%f\n", s6, atof(s6));
    printf("%10s\t%f\n", s7, atof(s7));

    return 0;
}

double atof(char s[])
{
    double val, power;
    int i, sign, esign, exponent, j;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        esign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        for (exponent = 0; isdigit(s[i]); i++)
            exponent = 10 * exponent + (s[i] - '0');
        if (esign == 1) {
            for (j = 0; j < exponent; j++)
                power /= 10.0;
        } else {
            for (j = 0; j < exponent; j++)
                power *= 10.0;
        }
    }
    return sign * val / power;
}   