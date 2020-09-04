#include <stdio.h>
#include <stdlib.h>     /* for atof() */

#define MAXOP   100     /* max size of operand or operator */
#define NUMBER  '0'     /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
double top(void);
void dupe(void);
void swap(void);
void clear(void);

/* KnR Exercise 04-04 add various stack functions
    I added a mute flag to prevent \n from executing pop
    after one of the stack functions are used. For
    example, using top should mute \n from exeucting pop,
    otherwise it defeats the purpose. */

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

/* top:     view the top value from stack without popping */
double top(void)
{
    if (sp > 0)
        return val[sp-1];
    else {
        printf("error: stack empty\n");
        return 0.0;     /* we should still return something */
    }
}

/* dupe:    duplicate the top value of the stack */
void dupe(void)
{
    void push(double); /* not sure if needed */
    double top(void);

    if (sp > 0)
        push(top());
    else
        printf("error: stack empty\n");
}

/* swap:    swaps the top 2 elements of the stack */
void swap(void)
{
    double temp;
    
    if (sp > 1)
        temp = val[sp-1], val[sp-1] = val[sp-2], val[sp-2] = temp;
    else
        printf("error: too few elements to swap");
}

/* clear:   clears the stack */
void clear(void)
{
    sp = 0;
}

#include <ctype.h>

/* getop:   get next operator or numeric operand */
int getop(char s[])
{
    int i, c;
    static char buffer = EOF;

    do {
        if (buffer == EOF) {
            c = getchar();
        } else {
            c = buffer;
            buffer = EOF;
        }
    } while ((s[0] = c) == ' ' || c == '\t');
    s[1] = '\0';
    if (c != '-' && !isdigit(c) && c != '.')
        return c;       /* not a number */
    i = 0;
    if (c == '-') {
        if (isdigit(c = getchar())) {
            s[++i] = c;
        } else {
            buffer = c;
            return '-'; /* not unary negative */
        }
    }
    if (isdigit(c))     /* collect integer part */
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.')       /* collect fraction part */
        while (isdigit(s[++i] = c = getchar()))
            ;
    s[i] = '\0';
    if (c != EOF)
        buffer = c;
    return NUMBER;
}