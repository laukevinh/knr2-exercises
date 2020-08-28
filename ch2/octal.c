#include <stdio.h>

int main()
{
    printf("char 63 %c\n", 63);
    printf("octal \\077 \077\n");       // 7 * 8 + 7 = 63
    printf("hexadecimal \\x3F \x3F\n"); // 3 * 16 + 15 = 63
    printf("char 64 %c\n", 64);
    printf("octal \\100 \100\n");       // 1 * 64 = 64
    printf("hexadecimal \\x40 \x40\n"); // 4 * 16 = 64
    printf("char 126 %c\n", 126);
    printf("octal \\176 \176\n");       // 1 * 64 + 7 * 8 + 6 = 126
    printf("hexadecimal \\x7E \x7E\n"); // 7 * 16 + 14 = 126
    printf("char -1 %c\n", -1);
    return 0;
}