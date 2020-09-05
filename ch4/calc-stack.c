#include <stdio.h>
#include "calc.h"

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