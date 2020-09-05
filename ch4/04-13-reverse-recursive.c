#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void reverse(char s[], int left, int right);

/* KnR Exercise 04-13   Write a recursive version of the 
    function reverse(s) , which reverses the string s in
    place. */

int main()
{
    char s1[] = "holiday";
    printf("%s\n", s1);
    reverse(s1, 0, strlen(s1)-1);
    printf("%s\n", s1);

    return 0;
}

void reverse(char s[], int left, int right)
{
    int c;
    if (left < right) {
        c = s[left];
        s[left] = s[right];
        s[right] = c;
        reverse(s, left + 1, right - 1);
    }
}