#include <stdio.h>

#define SIZE 1 << 26

int binsearch(int x, int v[], int n);

/* Test with linux `time` command 
    I had trouble with this problem. I had to 
    look at clc-wiki to get an idea of how to
    solve. This alternative version is slightly
    slower than the original because it doesn't
    test for v[mid] == x. It doesn't rely on
    those lucky instances. Instead, it will
    continue searching until the high-low range
    narrows down to 1 slot.  */

int main()
{
    int i, n;
    int v[SIZE];

    n = SIZE;
    for (i = 0; i < n; i++) {
        v[i] = i;
    }
    for (i = 0; i < n; i++) {
        binsearch(i, v, n);
    }
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low+high) / 2;
        if (x <= v[mid])
            high = mid;
        else
            low = mid + 1;
    }
    return (x == v[low]) ? low : -1;
}