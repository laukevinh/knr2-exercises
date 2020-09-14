/* KnR Exercise 06-04   Write a program that prints the
    distinct words in its input sorted into decreasing
    order of frequency of occurrence. Precede each word
    by its count.

    Build another tree that is ordered by count frequency
    rather than word. Two functions are used. `treesort`
    traverses the source tree and returns a pointer to
    each node. The pointers are passed into `addtree2`,
    which builds a new tree based on count value. 
    
    `treeprintrev` prints right most nodes first. */

#if !defined(TEST)
#define TEST "omit #if"
#endif
#define TEST2 "if" // if
#define TEST3 "if" /* if */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000
#define MAXWORD 100
struct tnode {
    char *word;
    int count;
    int linenums[MAXLINE];
    struct tnode *left;
    struct tnode *right;
};
struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
void treeprintrev(struct tnode *);
struct tnode *treesort(struct tnode *, struct tnode *);
char *left(char *, int);
int getword(char *, int);
int isnoise(char *s);

/* word frequency count */
int main(int argc, char *argv[])
{
    struct tnode *root, *root2;
    char word[MAXWORD];
    int n, linenum;

    if (argc != 2) {
        printf("Error: pass only 1 positive integer argument\n");
        return -1;
    }
    if ((n = atoi(argv[1])) <= 0) {
        printf("Error: %s not a positive integer\n", argv[1]);
        return -1;
    }
    root = root2 = NULL;
    while ((linenum = getword(word, MAXWORD)) != EOF)
        if (isalpha(word[0]) && !isnoise(word))
            root = addtree(root, left(word, n), linenum);
    root2 = treesort(root, root2);
    treeprintrev(root2);
    return 0;
}

struct tnode *talloc(void);
char *strdup2(char *);

/* addtree:     add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int linenum)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup2(w);
        p->count = 1;
        p->linenums[0] = linenum;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
        p->linenums[p->count - 1] = linenum;
    } else if (cond < 0)
        p->left = addtree(p->left, w, linenum);
    else
        p->right = addtree(p->right, w, linenum);
    return p;
}

/* treeprint:   in-order print of tree p */
void treeprint(struct tnode *p)
{
    int i;

    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s", p->count, p->word);
        for (i=0; i < p->count; i++)
            printf(" %d", p->linenums[i]);
        printf("\n");
        treeprint(p->right);
    }
}

/* treeprintrev:    reverse-order print of tree p */
void treeprintrev(struct tnode *p)
{
    if (p != NULL) {
        treeprintrev(p->right);
        printf("%4d %s\n", p->count, p->word);
        treeprintrev(p->left);
    }
}

struct tnode *addtree2(struct tnode *, struct tnode *);
void copyln(int *target, int *src, int count);

/* treesort:    sorts existing tree by count value */
struct tnode *
treesort(struct tnode *src, struct tnode *target)
{
    if (src != NULL) {
        target = treesort(src->left, target);
        target = addtree2(src, target);
        target = treesort(src->right, target);
    }
    return target;
}

/* addtree2:    creates a binary tree ordered by count */
struct tnode *
addtree2(struct tnode *src, struct tnode *target)
{
    if (target == NULL) {
        target = talloc();
        target->word = src->word;
        target->count = src->count;
        copyln(target->linenums, src->linenums, src->count);
        target->left = target->right = NULL;
    } else if (src->count <= target->count)
        target->left = addtree2(src, target->left);
    else
        target->right = addtree2(src, target->right);
    return target;
}

void copyln(int *target, int *src, int count)
{
    int i;

    for (i = 0; i < count; i++)
        target[i] = src[i];
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

int binsearch(char *word, char *noisewords[], int n);

/* isnoise:     return 1 if word is in noisewords, else 0 */
int isnoise(char *word)
{
    char *noisewords[] = {
        "a", "and", "as", "but", "from", "it", "like", "of",
        "on", "some", "to", "the", "with"
    };
    int cond;

    cond = binsearch(word, noisewords, 
                        sizeof noisewords / sizeof noisewords[0]);
    return cond >= 0;
}

/* binsearch:   find word in tab[0]...tab[n-1] */
int binsearch(char *word, char *tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

static int linenum = 1;     /* line number for word */

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
        if (c == '\n')
            linenum++;
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
            return linenum;
        }
    } else if (c == '#') {
        state = PREPROC;
    } else {
        *w = '\0';
        return (c == EOF) ? c : linenum;
    }
    while (state == QUOTES) {
        if ((c = getch()) == '\\')
            c = getch();    /* escaped so skip next c */
        else if (c == '\n')
            linenum++;
        else if (c == '\'' || c == EOF)
            break;
    }
    while (state == DBLQUOTES) {
        if ((c = getch()) == '\\')
            c = getch();    /* escaped so skip next c */
        else if (c == '\n')
            linenum++;
        else if (c == '"' || c == EOF)
            break;
    }
    while (state == LINECMT) {
        if ((c = getch()) == '\n' || c == EOF) {
            linenum++;
            break;
        }
    }
    while (state == BLKCMT) {
        if ((c = getch()) == '*') {
            if ((c = getch()) == '/')
                break;
            else
                ungetch(c);
        } else if (c == '\n') {
            linenum++;
        } else if (c == EOF)
            break;
    }
    while (state == PREPROC) {
        if (!isalnum(c = getch()) && c != '_') {
            if (c == '\n')
                linenum++;
            break;
        }
    }
    for ( ; state == CODE && --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return linenum;
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