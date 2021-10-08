#include <unistd.h>

/**
 * _output - writes the character c to stdout
 * @c: The character to print
 * Return: char to stdout
 */
int _output(int c)
{
	return (write(1, &c, 1));
}

/**
 * output - prints printable chars
 * @c: chars
 */
void output(int c)
{
	char prev = 0;

	if (c < ' ' && c != '\r' && c != '\n' && c != '\t' && c != '\b')
		return;
	if (c == '\n' && prev != '\r')
		_output('\r');
	_output(c);
	prev = c;
}
