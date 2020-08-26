#include <stdio.h>
#include <stdlib.h>

#define TAB 4

int main(void) {
  int c,i;

  i = 0;

  while ((c = getchar()) != EOF) {
    i++;
    if (c == '\n')
      i = 0; /* reset column counter */
    if (c == '\t') {
      while ((i % TAB) != 0) {
        putchar(' ');
        i++;
      }
    } else {
      putchar(c);
    }

  }
  return(0);
}