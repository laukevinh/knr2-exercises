#include <stdio.h>
#include <stdlib.h>     /* for atof() */

#define MAXOP   100     /* max size of operand or operator */
#define NUMBER  '0'     /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* KnR Exercise 05-10   Write the program expr, which evalutes
    a reverse Polish expression from the command line, where
    each operator or operand is a separate argument. For example
        expr 2 3 4 + * 
    evaluates to 2 * (3 + 4). 
    
    Resued most of the existing code from previous exercises,
    only changing getop and the while loop test condition
    in main. Remember to escape multiplication * so that the
    shell doesn't expand it, which will cause errors. */

/* reverse Polish calculator */
int main(int argc, char *argv[])
{
    int type, nerror;
    double op2;

    nerror = 0;
    while (--argc > 0) {
        switch (getop(*++argv)) {
        case NUMBER:
            push(atof(*argv));
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
            else {
                argc = 0;
                nerror++;
                printf("error: zero divisor\n");
            }
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push((int) pop() % (int) op2);
            else {
                argc = 0;
                nerror++;
                printf("error: modulo zero\n");
            }
            break;
        default:
            argc = 0;
            nerror++;
            printf("error: unknown command %s\n", *argv);
            break;
        }
    }
    if (nerror > 0)
        return -1;
    printf("\t%.8g\n", pop());
    return 0;
}

#define MAXVAL  100     /* maximum depth of val stack */

int sp = 0;             /* next free stack poisiton */
double val[MAXVAL];     /* value stack */

/* push:    push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop:     pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>

/* getop:   get next operator or numeric operand */
int getop(char s[])
{
    int c;

    if ((c = *s++) != '-' && !isdigit(c) && c != '.')
        return c;       /* not a number */
    if (c == '-' && *s == '\0')
        return c;
    if (c == '-' && !isdigit(*s) && *s != '.')
        return -1;
    while (isdigit(*s))     /* collect integer part */
        s++;
    if (*s == '.')          /* collect fraction part */
        while (isdigit(*s))
            s++;
    return (*s == '\0') ? NUMBER : -1;
}