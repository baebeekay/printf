#ifndef _MAIN_H
#define _MAIN_H

#define putchar(c) output(c)
#define RIGHT 1
#define ZERO 2
#define HASH 3
#define PLUS 4
#define SPACE 8
#define PRINT_BUF_LEN 1024

int _printf(const char *format, ...);
void _output(int c);
void printchar(char **str, int c);
int prints(char **out, const char *string, int width, int pad);
int printi(char **out, int i, int b, int sg, int width, int pad, int letbase);
int print(char **out, const char *format, va_list args);



#endif
