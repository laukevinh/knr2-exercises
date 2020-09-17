#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *);

int main()
{
    struct nlist *repl;
    char t[MAXLINE];
    char s[] = "Yo"
        "His palms are sweaty, knees weak, arms are heavy"
        "There's vomit on his sweater already, mom's spaghetti";

    repl = NULL;
    install("heavy", "steady");
    repl = lookup("heavy");
    printf("%s\n", (repl == NULL) ? "Not found" : repl->defn);
    undef("heavy");
    repl = lookup("heavy");
    printf("%s\n", (repl == NULL) ? "Not found" : repl->defn);
    return 0;
}

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

/* hash:    form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup:  look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

#include <stdlib.h>

struct nlist *lookup(char *);
char *strdup2(char *);

/* install:     put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup2(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *) np->defn);
    if ((np->defn = strdup2(defn)) == NULL)
        return NULL;
    return np;
}

char *strdup2(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

void undef(char *name)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) != NULL) {
        hashval = hash(name);
        hashtab[hashval] = np->next;
        free((void *) np->name);
        free((void *) np->defn);
    }
}