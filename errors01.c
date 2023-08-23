#include "shell.h"

/**
 *_eputs - prints an input.
 * @str: string
 * Return: None
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes to stdrr.
 * @d: The variable of a character
 * Return: On success 1.
 * On error, -1 is returned.
 */
int _eputchar(char d)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (d != BUF_FLUSH)
		buf[i++] = d;
	return (1);
}

/**
 * _putfd - writes character to given fd.
 * @d: The character to print
 * @fd: The filedescriptor.
 * Return: On success 1.
 * On error, -1 is returned.
 */
int _putfd(char d, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (d != BUF_FLUSH)
		buf[i++] = d;
	return (1);
}

/**
 *_putsfd - prints a string.
 * @str: string variable.
 * @fd: the fd.
 * Return: the number of chars.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
