#include <stdio.h>

#define TABSIZE 4

void print_blanks(int n);

int main()
{
	int offset = 0;
	int ch = 0;
	int padding = 0;
	int blank_counter = 0;
    
	while ((ch = getchar()) != EOF)	{
		if (ch == '\n')	{
			print_blanks(blank_counter);
			blank_counter = 0;
			offset = 0;
			putchar(ch);
		} else if (ch == ' ') {
			if (blank_counter == 0) {
				padding = TABSIZE - (offset % TABSIZE);
			}
			offset += 1;
			blank_counter += 1;
			if (blank_counter == padding) {
				putchar('\t');
				blank_counter = 0;
			}
		} else if (ch == '\t') {
			print_blanks(blank_counter);
			blank_counter = 0;
			offset += TABSIZE - (offset % TABSIZE);
			putchar(ch);
		} else {
			print_blanks(blank_counter);
			blank_counter = 0;
			offset += 1;
			putchar(ch);
		}
	}
}

void print_blanks(int n)
{
	for (int i = 0; i < n; i++) {
		putchar(' ');
	}
}