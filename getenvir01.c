#include "shell.h"

/**
 * get_environ - string array copy of the environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments.
 *  Return: 1 on delete, 0 otherwise.
 * @var: the string variable.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *k;

	if (!node || !var)
		return (0);

	while (node)
	{
		k = starts_with(node->str, var);
		if (k && *k == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable.
 * @info: Structure containing potential arguments.
 * @var: the string variable.
 * @val: the string variable value.
 *  Return: Always 0.
 */
int _setenv(info_t *info, char *var, char *val)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !val)
		return (0);

	buf = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, val);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
