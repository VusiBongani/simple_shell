#include "shell.h"

/**
 * input_buf - buffers
 * @info: parameter for struct
 * @buf: buffer address
 * @length1: length address
 * Return: returns bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *length1)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*length1)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			{
				*length1 = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - obtains a line
 * @info: struct parameter
 * Return: returns bytes
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, length1;
	ssize_t t = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	t = input_buf(info, &buf, &length1);
	if (t == -1)
		return (-1);
	if (length1)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, length1);
		while (j < length1)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length1)
		{
			i = length1 = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (t);
}

/**
 * read_buf - reads a buffer
 * @info: struct parameter
 * @buf: buffer
 * @t: size
 * Return: returns r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *t)
{
	ssize_t r = 0;

	if (*t)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*t = r;
	return (r);
}

/**
 * _getline - obtains the line
 * @info: struct parameter
 * @ptr: pointer to buffer
 * @sizel: returns the size if not NULL
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *sizel)
{
	static char buf[READ_BUF_SIZE];
	static size_t u, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && sizel)
		s = *sizel;
	if (u == len)
		u = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + u, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + u, k - u);
	else
		_strncpy(new_p, buf + u, k - u + 1);

	s += k - u;
	u = k;
	p = new_p;

	if (sizel)
		*sizel = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - cancels out Ctrl C.
 * @sig_num: represents the signal number.
 * Return: returns void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
