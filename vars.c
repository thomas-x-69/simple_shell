#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	// Check for "||" (logical OR)
	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	// Check for "&&" (logical AND)
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	// Check for ";" (command chain delimiter)
	else if (buf[j] == ';')
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*p = j;
	return (1);
}

/**
 * check_chain - checks if we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	// Check for CMD_AND and non-zero status
	if (info->cmd_buf_type == CMD_AND && info->status)
	{
		buf[i] = 0;
		j = len;
	}
	// Check for CMD_OR and zero status
	if (info->cmd_buf_type == CMD_OR && !info->status)
	{
		buf[i] = 0;
		j = len;
	}

	*p = j;
}

/**
 * replace_alias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	// Loop through alias attempts (up to 10)
	for (i = 0; i < 10; i++)
	{
		// Search for an alias that starts with the current command
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		// Free the old argv[0] and duplicate the alias value
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	// Loop through each token in argv
	for (i = 0; info->argv[i]; i++)
	{
		// Check if the token starts with '$' and has more than one character
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		// Check for special variables "$?" and "$$"
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}

		// Search for environment variable in the env list
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}

		// Replace the token with an empty string if not found
		replace_string(&info->argv[i], _strdup(""));
	}

	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	// Free the old string and assign the new one
	free(*old);
	*old = new;
	return (1);
}
