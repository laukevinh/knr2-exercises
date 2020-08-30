#include <stdio.h>

#define MAXLINE 1000

void expand(char s1[], char s2[]);

/* pseudocode
    while there are more chars
        if char is letter or num
            letter and num count +1
            if no dashes yet
                save char as c
            else if c < char
                put c through char in s2
                reset dash count
        else if char is dash
            if no letter or nums yet
                put dash in s2
            else
                dash count +1
    if last char was dash
        put dash in s2
    add \0 to s2 */

int main()
{
    char s1[MAXLINE];

    char s2[MAXLINE] = "a-z";
    expand(s2, s1);
    printf("%s\t\t%s\n", s2, s1);

    char s3[MAXLINE] = "a-b-c";
    expand(s3, s1);
    printf("%s\t\t%s\n", s3, s1);

    char s4[MAXLINE] = "a-z0-9";
    expand(s4, s1);
    printf("%s\t\t%s\n", s4, s1);

    char s5[MAXLINE] = "-a-z";
    expand(s5, s1);
    printf("%s\t\t%s\n", s5, s1);

    char s6[MAXLINE] = "A-Z0-9-";
    expand(s6, s1);
    printf("%s\t\t%s\n", s6, s1);

    return 0;
}

void expand(char s1[], char s2[])
{
    int c, i, j, nalphanum, ndash;

    i = j = ndash = nalphanum = 0;
    for (i=0; s1[i] != '\0'; i++) {
        if ((s1[i]>='0' && s1[i]<='9')
                || (s1[i]>='a' && s1[i]<='z')
                || (s1[i]>='A' && s1[i]<='Z')) {
            nalphanum++;
            if (ndash == 0) {
                c = s1[i];
            } else if (c < s1[i]) {
                while (c < s1[i]) {
                    s2[j++] = c;
                    c++;
                }
                s2[j++] = c;
                ndash = 0;
            }
        } else if (s1[i] == '-') {
            if (nalphanum == 0) {
                s2[j++] = s1[i];
            } else {
                ndash++;
            }
        }
    }
    if (s1[i-1] == '-') {
        s2[j++] = '-';
    }
    s2[j] = '\0';

}