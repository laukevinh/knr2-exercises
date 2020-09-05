#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXLINE 1000

int itoa(int n, char s[], int position);

/* KnR Exercise 04-12   Adapt the ideas of printd to 
    write a recursive version of itoa; that is, convert 
    an integer into a string by calling a recursive 
    routine.

    I added the 3rd parameter int position to itoa to avoid
    using static variables. Addressing INT_MIN is simple as
    long as the recursive call is timed correctly. 

    Pseudocode
        IF n < 0
            Reduce abs val of n by 1,
            Flip to postiive, mod 10 for remainder,
            Increase Least Significant Digit of remainder
            so it is equal to LSD of original n
            Save value
            Truncate LSD
            Make n positive (for all subsequent recursions)
            Recursive call to get next significant digit
        ELSE
            Save LSD
            Recursive call to get next significant digit
        Write saved value to s[i] (i is greatest at top of stack)
        Cap off s[] with '\0'
        return i (inc by 1 per exit to track stack) */

int main()
{
    char s[MAXLINE];
    int i;

    i = 1234567890;
    itoa(i ,s, 0);
    printf("%40d\t%s\n", i, s);

     i = -1234567890;
    itoa(i ,s, 0);
    printf("%40d\t%s\n", i, s);

    i = (1 << 31) - 1;
    itoa(i ,s, 0);
    printf("%40d\t%s\n", i, s);

    i = -(1 << 31);
    itoa(i ,s, 0);
    printf("%40d\t%s\n", i, s);

    return 0;
}

int itoa(int n, char s[], int pos)
{
    int c;

    if (n < 0) {
        s[pos++] = '-';
        c = ((-(n+1) % 10) + 1) % 10 + '0';
        n = -(n / 10);
        pos = itoa(n, s, pos);
    } else {
        c = n % 10 + '0';
        if (n / 10)
            pos = itoa(n / 10, s, pos);
    }
    s[pos++] = c;
    s[pos] = '\0';
    return pos;
}