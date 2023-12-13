#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
    /* Initialize fields of the info_t struct to default values */
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
    int i = 0;

    /* Set the fname field to the program name */
    info->fname = av[0];

    /* Tokenize the argument string and store it in the argv field */
    if (info->arg)
    {
        info->argv = strtow(info->arg, " \t");

        /* If tokenization fails, manually allocate memory for argv and store the argument */
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = _strdup(info->arg);
                info->argv[1] = NULL;
            }
        }

        /* Count the number of arguments (elements in argv) */
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        /* Replace aliases and variables in the argument */
        replace_alias(info);
        replace_vars(info);
    }
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
    /* Free the argv field and set it to NULL */
    ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;

    /* Free additional fields if the 'all' flag is set */
    if (all)
    {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            free_list(&(info->env));
        if (info->history)
            free_list(&(info->history));
        if (info->alias)
            free_list(&(info->alias));
        ffree(info->environ);
        info->environ = NULL;
        bfree((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        _putchar(BUF_FLUSH);
    }
}
