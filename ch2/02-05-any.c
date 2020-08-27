#include <stdio.h>

int any(char s1[], char s2[]);

int main()
{
    char s1[] = "Last name ever";
    char s2[] = "abcd";
    printf("%40s %10s %10d\n", s1, s2, any(s1, s2));
    char s3[] = "First name greatest";
    printf("%40s %10s %10d\n", s3, s2, any(s3, s2));
    char s4[] = "Like a sprained ankle boy ain't...";
    printf("%40s %10s %10d\n", s4, s2, any(s4, s2));
    char s5[] = "...nothing to play with";
    printf("%40s %10s %10d\n", s5, s2, any(s5, s2));
    char s6[] = ".........";
    printf("%40s %10s %10d\n", s6, s2, any(s6, s2));


    return 0;
}

int any(char s1[], char s2[])
{
    int i, j;

    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }
    return -1;
}