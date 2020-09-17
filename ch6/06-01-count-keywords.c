/* KnR Exercise 06-01   Our version of getword does not 
    properly handle underscores, string constants, comments, 
    or preprocessor control lines. Write a better version.

    Spent quite a bit of time on this one. Just track
    the state and use a temporary variable (e.g. char c)
    to skip over underscore, string constants, comments,
    and preprocessor control lines. Use *w when state
    is valid code and need to track the word. */

struct key {
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "if", 0,
    /* ... */
    /* test keyword break */
    // test keyword break
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

#if !defined(TEST)
#define TEST "omit #if"
#endif

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main()
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n",
                keytab[n].count, keytab[n].word);
    return 0;
}

/* binsearch:   find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* getword:     get next word or character from input */
int getword(char *word, int lim)
{
    int c, state, getch(void);
    void ungetch(int);
    char *w = word;
    enum states { 
        NONE, CODE, QUOTES, DBLQUOTES, LINECMT, BLKCMT,
        PREPROC
    };

    state = CODE;
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (isalpha(c) || c == '_') {
        state = CODE;
    } else if (c == '\'') {
        state = QUOTES;
    } else if (c == '"') {
        state = DBLQUOTES;
    } else if (c == '/') {
        if ((c = getch()) == '/') {
            state = LINECMT;
        } else if (c == '*') {
            state = BLKCMT;
        } else {
            ungetch(c);
            return '/';
        }
    } else if (c == '#') {
        state = PREPROC;
    } else {
        *w = '\0';
        return c;
    }
    while (state == QUOTES) {
        if ((c = getch()) == '\\')
            c = getch();    /* escaped so skip next c */
        else if (c == '\'' || c == EOF)
            break;
    }
    while (state == DBLQUOTES) {
        if ((c = getch()) == '\\')
            c = getch();    /* escaped so skip next c */
        else if (c == '"' || c == EOF)
            break;
    }
    while (state == LINECMT) {
        if ((c = getch()) == '\n' || c == EOF)
            break;
    }
    while (state == BLKCMT) {
        if ((c = getch()) == '*') {
            if ((c = getch()) == '/')
                break;
            else
                ungetch(c);
        } else if (c == EOF)
            break;
    }
    while (state == PREPROC) {
        if (!isalnum(c = getch()) && c != '_')
            break;
    }
    for ( ; state == CODE && --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

#define BUFSIZE 1

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

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