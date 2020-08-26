#include <stdio.h>



#define S3 3 

#define S4 "S4 misleading comment block*/"
#define S5 "/* S5 Test Passed */"
#define S6 "// S6 Test Passed"
#define S7  "S7 Test Passed"
#define S8  "S8 Test Passed */"
#define S9  "S9 Test Passed"
#define S10 "This is also a really really long line /* that should show up */ and the comment at the end should be removed" 
#define S11  "Back to back comments" 
#define PRINT 1
#define INCMTLINE 2
#define INCMTBLOCK 3
#define INQUOTES 4
#define HOLD 5

int main()
{
    int ch, prev_ch, status;

    status = PRINT;

    while ((ch=getchar()) != EOF) {
        if (status == INCMTBLOCK) {
            if (prev_ch == '*' && ch == '/') {
                status = PRINT;
            }
        } else if (status == INCMTLINE) {
            if (ch == '\n') {
                putchar(ch);
                status = PRINT;
            }
        } else if (status == HOLD) {
            if (ch=='/') {
                status = INCMTLINE;
            } else if (ch=='*') {
                status = INCMTBLOCK;
            } else {
                putchar('/');
                putchar(ch);
                status = PRINT;
            }
        } else if (status == INQUOTES) {
            putchar(ch);
            if (ch == '"') {
                status = PRINT;
            }
        } else if (status == PRINT) {
            if (ch=='/') {
                status = HOLD;
            } else {
                putchar(ch);
                if (ch == '"') {
                    status = INQUOTES;
                }
            }
        }
        prev_ch = ch;
    }
    return 0;
}


