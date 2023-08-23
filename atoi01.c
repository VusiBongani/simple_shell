#include "shell.h"

/**
 * interactive - returns true
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks whether character is delimeter
 * @b: the character to check
 * @delim: Delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char b, char *delim)
{
	while (*delim)
		if (*delim++ == b)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabets
 *@b: The input character
 *Return: 1 if b is an  alphabet, 0 otherwise
 */

int _isalpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@v: represent the string
 *Return: 0 if a certain condition is not
 */

int _atoi(char *v)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  v[i] != '\0' && flag != 2; i++)
	{
		if (v[i] == '-')
			sign *= -1;

		if (v[i] >= '0' && v[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (v[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

