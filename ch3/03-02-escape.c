#include <stdio.h>

#define MAXLINE 1000

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main()
{
    char s[MAXLINE];
    char t[MAXLINE] = "New line \nTabs\t1\t2\t3\nEnd.";

    printf("%s\n", t);
    escape(s, t);
    printf("%s\n", s);
    unescape(s, s);
    printf("%s\n", s);

    return 0;
}

void escape(char s[], char t[])
{
    int i, j, c;
    
    i = j = 0;
    while ((c = t[i++]) != '\0') {
        switch (c) {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        default:
            s[j++] = c;
            break;
        }
    }
    s[j] = '\0';
}

void unescape(char s[], char t[])
{
    int i, j, c;
    int nslash;
    
    i = j = nslash = 0;
    while ((c = t[i++]) != '\0') {
        switch (c) {
        case '\\':
            ++nslash;
            if (nslash > 1) {
                s[j++] = '\\';
                s[j++] = '\\';
                nslash = 0;
            }
            break;
        case 'n':
            if (nslash == 1) {
                s[j++] = '\n';
                nslash = 0;
            } else {
                s[j++] = c;
            }
            break;
        case 't':
            if (nslash == 1) {
                s[j++] = '\t';
                nslash = 0;
            } else {
                s[j++] = c;
            }
            break;
        default:
            s[j++] = c;
            break;
        }
    }
    s[j] = '\0';
}