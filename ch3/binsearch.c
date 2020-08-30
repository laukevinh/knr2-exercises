#include <stdio.h>

#define SIZE 1 << 26

int binsearch(int x, int v[], int n);

/* Test with linux `time` command */

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
    while (low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}