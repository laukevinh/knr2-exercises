/* KnR Exercise 06-02   Write a program that reads a C 
    program and prints in alphabetical order each group
    of variable names that are identical in the first 6
    characters but different somewhere thereafter.
    Don't count words within strings and comments. Make
    6 a parameter that can be set from the command line.

    I made a left function that returns the first n
    characters in a word. I only changed main to include
    some error checking for command line parameters and
    used `left` on word before passing into `addtree`. 
    Everything else remains the same.
    
    Pseudocode
    while more input
        if word
            get first n chars
            add to tree */

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

#if !defined(TEST)
#define TEST "omit #if"
#endif
#define TEST2 "if" // if
#define TEST3 "if" /* if */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
char *left(char *, int);
int getword(char *, int);

/* word frequency count */
int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];
    int n;

    if (argc > 2) {
        printf("Error: too many arguments\n");
        return -1;
    }
    if ((n = atoi(argv[1])) <= 0) {
        printf("Error: %s not a positive integer\n", argv[1]);
        return -1;
    }
    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, left(word, n));
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *strdup2(char *);

/* addtree:     add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup2(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

/* treeprint:   in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

#include <stdlib.h>

/* talloc:  make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup2(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

char *left(char *s, int n)
{
    char *t;
    int i;

    for (i=0, t=s; i<n && *t!='\0'; i++, t++)
        ;
    *t = '\0';
    return s;
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