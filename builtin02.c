#include "shell.h"

/**
 * _myhistory - displays the history list.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - alias to string.
 * @info: parameter struct.
 * @str: string alias
 * Return: Returns value.
 */
int unset_alias(info_t *info, char *str)
{
	char *r, c;
	int val;

	r = _strchr(str, '=');
	if (!r)
		return (1);
	c = *r;
	*r = 0;
	val = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*r = c;
	return (val);
}

/**
 * set_alias - sets alias to string.
 * @info: parameter struct.
 * @str: the string alias.
 * Return: Returns Values
 */
int set_alias(info_t *info, char *str)
{
	char *r;

	r = _strchr(str, '=');
	if (!r)
		return (1);
	if (!*++r)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: Returns Values
 */
int print_alias(list_t *node)
{
	char *r = NULL, *b = NULL;

	if (node)
	{
		r = _strchr(node->str, '=');
		for (b = node->str; b <= r; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(r + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *t = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		t = _strchr(info->argv[i], '=');
		if (t)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
