#include <stdio.h>

/* Scenario 1: Regular text */
/* Scenario 2: multiple lines
    line 2
    line 3 */
#define S3 3 // Scenario 3, in line comment
// Scenario 4: /* S4 fails if this shows up
#define S4 "S4 misleading comment block*/"
#define S5 "/* S5 Test Passed */"
#define S6 "// S6 Test Passed"
#define S7 /* Scenario 7: in between */ "S7 Test Passed"
#define S8 /* Scenario 8: "/* Cmts don't nest */ "S8 Test Passed */"
#define S9 /* A really long line 00000000000000000000000000000000000000000000000000000 111111111111111111111111111
    0000000000000000000000000000000000000000000000000000 */ "S9 Test Passed"
#define S10 "This is also a really really long line /* that should show up */ and the comment at the end should be removed" /* S10 Fails if this shows up */
#define S11 /* Scenario 11: */ "Back to back comments" //S11 fails if this shows up
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
            if (ch=='*') {
                status = INCMTBLOCK;
            } else if (ch=='/') {
                status = INCMTLINE;
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


