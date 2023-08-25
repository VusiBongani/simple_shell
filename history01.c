#include "shell.h"

/**
 * get_history_file - Obtains the history file
 * @info: parameter struct
 * Return: returns the allocated string
 */

char *get_history_file(info_t *info)
{
	char *buf, *direc;

	direc = _getenv(info, "HOME=");
	if (!direc)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(direc) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, direc);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates or appends to an existing file
 * @info: parameter struct
 * Return: return a value
 */
int write_history(info_t *info)
{
	ssize_t fdr;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fdr = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdr == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fdr);
		_putfd('\n', fdr);
	}
	_putfd(BUF_FLUSH, fdr);
	close(fdr);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: parameter struct
 * Return: returns value
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fdr, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fdr = open(filename, O_RDONLY);
	free(filename);
	if (fdr == -1)
		return (0);
	if (!fstat(fdr, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fdr, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fdr);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to linked list
 * @info: Structure containing potential arguments.
 * @buf: buffer
 * @countline: the history linecount.
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int countline)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, countline);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumber history after changes.
 * @info: Structure containing potential arguments.
 * Return: returns value
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int p = 0;

	while (node)
	{
		node->num = p++;
		node = node->next;
	}
	return (info->histcount = p);
}
