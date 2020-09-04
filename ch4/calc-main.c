#include <stdio.h>
#include <stdlib.h>     /* for atof() */
#include "calc.h"

#define MAXOP   100     /* max size of operand or operator */

/* Example of splitting calculator program into several files. 
    
    `gcc calc-main.c calc-stack.c calc-getch.c calc-getop.c`*/

/* reverse Polish calculator */
int main()
{
    int type, mute;
    double op2;
    char s[MAXOP];
    enum boolean { FALSE, TRUE };

    mute = FALSE;
    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push((int) pop() % (int) op2);
            else
                printf("error: modulo zero\n");
            break;
        case 't':
            printf("\t%.8g\n", top());
            mute = TRUE;
            break;
        case 'u':
            dupe();
            mute = TRUE;
            break;
        case 'w':
            swap();
            mute = TRUE;
            break;
        case 'c':
            clear();
            mute = TRUE;
            break;
        case '\n':
            if (mute)
                mute = FALSE;
            else
                printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}