#include <stdio.h>
#include <stdlib.h>     /* for atof() */
#include <math.h>       /* for sin, exp and pow */
#include <string.h>     /* for strlen() */

#define MAXLINE 1000    /* max size of getline */
#define MAXOP   100     /* max size of operand or operator */
#define MAXVARS 26      /* max size of storage array */
#define NUMBER  '0'     /* signal that a number was found */
#define TOP     't'     /* signal for top command */
#define DUPE    'u'     /* signal for duplicate command */
#define SWAP    'w'     /* signal for swap command */
#define CLEAR   'c'     /* signal for clear command */
#define SIN     's'     /* signal for sin function */
#define EXP     'e'     /* signal for exp function */
#define POW     '^'     /* signal for pow function */
#define RECENT  '_'
#define SETVAR  1       /* signal to set variable */
#define GETVAR  2       /* signal to get variable */

int getline2(char s[], int lim);
int getop(char line[], char op[]);
void push(double);
double pop(void);
double top(void);
void dupe(void);
void swap(void);
void clear(void);

/* KnR Exercise 04-10   An alternate organization uses getline
    to read an entireinput line; this makes getch and ungetch
    unnecessary. Revise the calculator to use this approach.

     */

/* reverse Polish calculator */
int main()
{
    int type, mute, len, i;
    double op2, recent;
    double vars[MAXVARS];
    char s[MAXLINE];
    char t[MAXOP];
    enum boolean { FALSE, TRUE };

    mute = FALSE;
    for (i=0; i<MAXVARS; i++)
        vars[i] = 0;
    while ((len = getline2(s, MAXLINE)) > 0) {
        while ((type = getop(s, t)) != EOF) {
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
            case TOP:
                printf("\t%.8g\n", recent = top());
                mute = TRUE;
                break;
            case DUPE:
                dupe();
                mute = TRUE;
                break;
            case SWAP:
                swap();
                mute = TRUE;
                break;
            case CLEAR:
                clear();
                mute = TRUE;
                break;
            case SIN:
                push(sin(pop()));
                break;
            case EXP:
                push(exp(pop()));
                break;
            case POW:
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case SETVAR:
                vars[s[0] - 'A'] = top();
                mute = TRUE;
                break;
            case GETVAR:
                push(vars[s[0] - 'A']);
                break;
            case RECENT:
                push(recent);
                break;
            case '\n':
                if (mute) {
                    mute = FALSE;
                } else {
                    printf("\t%.8g\n", recent = pop());
                }
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
            }
        }
    }
    return 0;
}

int getline2(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
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

int bufp = 0;       /* next free position in buf */
int getch(void);
void ungetch(int);
void ungets(char s[]);

/* getop:   get next operator or numeric operand */
int getop(char s[], char t[])
{
    int i, c, sign;

    while((t[0] = c = s[bufp++]) == ' ' || c == '\t')
        ;
    t[1] = '\0';
    if (c != '-' && !isdigit(c) && c != '.' && c != '|' 
            && (c < 'A' || c > 'Z'))
        return c;       /* not a number, command or variable */
    if (c == '|') {
        c = s[bufp++];
        if (c >= 'A' && c <= 'Z') {
            t[0] = c;
            return SETVAR;
        } else {
            bufp--;
            return '|';
        }
    }
    if (c >= 'A' && c <= 'Z') {
        return GETVAR;
    }
    i = 0;
    if (c == '-') {
        if (isdigit(c = s[bufp++])) {
            t[++i] = c;
        } else {
            bufp--;
            return '-'; /* not unary negative */
        }
    }
    if (isdigit(c))     /* collect integer part */
        while (isdigit(t[++i] = c = s[bufp++]))
            ;
    if (c == '.')       /* collect fraction part */
        while (isdigit(t[++i] = c = s[bufp++]))
            ;
    t[i] = '\0';
    if (c != EOF)
        bufp--;
    return NUMBER;
}

#define BUFSIZE 1

char buf[BUFSIZE];  /* buffer for ungetch */


int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(char s[])
{
    int i, len;

    len = strlen(s);
    if (len > BUFSIZE - bufp) {
        printf("ungets: too many characters\n");
    } else {
        while (len > 0)
            ungetch(s[--len]);
    }
}