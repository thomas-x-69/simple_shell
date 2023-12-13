#include "shell.h"

/**
 * _myhistory - displays the history list, one command per line, preceded
 *              with line numbers starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
    /* Print the history list */
    print_list(info->history);
    return (0);
}

/**
 * unset_alias - removes an alias from the alias list
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    /* Find the position of '=' in the alias string */
    p = _strchr(str, '=');
    if (!p)
        return (1);

    /* Temporarily replace '=' with null terminator */
    c = *p;
    *p = 0;

    /* Delete the node at the index corresponding to the alias */
    ret = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

    /* Restore '=' to the original position */
    *p = c;

    return (ret);
}

/**
 * set_alias - sets an alias in the alias list
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    /* Find the position of '=' in the alias string */
    p = _strchr(str, '=');
    if (!p)
        return (1);

    /* If the character immediately after '=' is null, unset the alias */
    if (!*++p)
        return (unset_alias(info, str));

    /* Unset the alias to avoid duplicates and add it to the alias list */
    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    /* Check if the node is valid */
    if (node)
    {
        /* Find the position of '=' in the alias string */
        p = _strchr(node->str, '=');

        /* Print the alias name */
        for (a = node->str; a <= p; a++)
            _putchar(*a);

        /* Print the alias value in single quotes */
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return (0);
    }

    /* Return 1 if the node is invalid */
    return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    /* If no arguments are provided, print all aliases */
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

    /* Process each argument */
    for (i = 1; info->argv[i]; i++)
    {
        /* Find the position of '=' in the argument */
        p = _strchr(info->argv[i], '=');

        /* If '=' is found, set an alias; otherwise, print the alias */
        if (p)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
