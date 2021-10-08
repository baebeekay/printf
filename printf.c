#include <stdarg.h>
#include "main.h"

/**
 * printchar - prints the characters
 * @str: pointer to char
 * @c: integer character
 */
void printchar(char **str, int c)
{
	int putchar(int c);

	if (str)
	{
		**str = c;
		++(*str);
	}
	else
	{
		(void) putchar(c);
	}
}

/**
 * prints - handles space and width
 * @out: pointer arg
 * @string:pointer arg
 * @width: character strings
 * @pad: space pad
 * Return: int
 */
int prints(char **out, const char *string, int width, int pad)
{
	int pc = 0, padchar = ' ';
	int len = 0;
	const char *ptr;

		if (width > 0)
		{
			for (ptr = string; *ptr; ++ptr)
				++len;
			if (len >= width)
				width = 0;
			else
				width -= len;
			if (pad & ZERO)
				padchar = '0';
		}
		if (!(pad && RIGHT))
		{
			for (; width > 0; --width)
			{
				printchar (out, padchar);
				++pc;
			}
		}
		for (; *string ; ++string)
		{
			printchar (out, *string);
			++pc;
		}
		for (; width > 0; --width)
		{
			printchar (out, padchar);
			++pc;
		}

		return (pc);
}

/**
 * printi - handles the buffer lenght
 * @out: pointer arg
 * @i:second arg
 * @b: thrid arg
 * @sg: fouth arg
 * @width: fifth arg
 * @pad: sixth arg
 * @letbase: seventh arg
 * Return: buff len
 */
int printi(char **out, int i, int b, int sg, int width, int pad, int letbase)
{
	char print_buf[PRINT_BUF_LEN];
	char *s;
	int t, neg = 0, pc = 0;
	unsigned int u = i;

	if (i == 0)
	{
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return (prints(out, print_buf, width, pad));
	}

	if (sg && b == 10 && i < 0)
	{
		neg = 1;
		u = -i;
	}

	s = print_buf + PRINT_BUF_LEN - 1;
	*s = '\0';

	while (u)
	{
		t = u % b;
		if (t >= 10)
			t += letbase - '0' - 10;
		*--s = t + '0';
		u /= b;
	}

	if (neg)
	{
		if (width && (pad & ZERO))
		{
			printchar (out, '-');
			++pc;
			--width;
		}
		else
		{
			*--s = '-';
		}
	}

	return (pc + prints(out, s, width, pad));
}

/**
 * print - handles flags ang formats
 * @out: pointer arg
 * @format: specifiers
 * @args: variable list
 * Return: 0
 */
int print(char **out, const char *format, va_list args)
{
	int width, flag;
	int pc = 0;
	char scr[2];

	for (; *format != 0; ++format)
	{
		if (*format == '%')
		{
			++format;
			width = flag = 0;
			if (*format == '\0')
				break;
			if (*format == '%')
				goto out;

			while (*format == 0)
			{
				++format;
				if (*format == '-')
				{
					flag |= RIGHT;
				}
				if (*format == '0')
				{
					flag |= ZERO;
				}
				if (*format == '+')
				{
					flag |= PLUS;
				}
				if (*format == '#')
				{
					flag |= HASH;
				}
				if (*format == ' ')
				{
					flag |= SPACE;
				}
			}
			for ( ; *format >= '0' && *format <= '9'; ++format)
			{
				width *= 10;
				width += *format - '0';
			}
			if (*format == 's')
			{
				char *s = va_arg(args, char *);

				pc += prints(out, s ? s : "(null)",
					      width, flag);
				continue;
			}
			if (*format == 'd' || *format == 'i')
			{
				pc += printi(out, va_arg(args, int),
					     10, 1, width, flag, 'a');
				continue;
			}
			if (*format == 'x' || *format == 'X')
			{
				pc += printi(out, va_arg(args, int),
					     16, 0, width, flag, 'a');
				continue;
			}
			if (*format == 'u')
			{
				pc += printi(out, va_arg(args, int),
					     10, 0, width, flag, 'a');
				continue;
			}
			if (*format == 'c')
			{
				/* char are converted to int then pushed on the stack */
				scr[0] = (char)va_arg(args, int);
				scr[1] = '\0';
				pc += prints(out, scr, width, flag);
				continue;
			}
			if (*format == 'o')
			{
				pc += printi(out, va_arg(args, int),
					      8, 0, width, flag, 'a');
			}
			if (*format == 'p')
			{
				if (width == -1)
				{
					width = 2 * sizeof(void *);
				}
				pc += printi
					(out,
					 (unsigned long)va_arg(args, void *)
					 , 16, 0, width, flag, 'A');
				continue;
			}
			if (*format == 'r')
			{
				char *p = (va_arg(args, char *));

				pc += prints(out, p, width, flag);
				continue;
			}
		}
		else
		{ out:
			printchar (out, *format);
			++pc;
		}
	}
	if (out)
		**out = '\0';
	va_end(args);
	return (pc);
}

/**
 * _printf - prints to stdout
 * @format: specifier
 * Return: format, args
 */
int _printf(const char *format, ...)
{
	va_list args;

	va_start(args, format);
	return (print(0, format, args));
}
