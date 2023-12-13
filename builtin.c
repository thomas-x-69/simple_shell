#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 * Return: exits with a given exit status
 *         (0) if info->argv[0] != "exit"
 */
int _myexit(info_t *info)
{
    int exitcheck;

    /* Check if there is an exit argument */
    if (info->argv[1])
    {
        /* Convert the exit argument to an integer */
        exitcheck = _erratoi(info->argv[1]);

        /* Handle the case where the exit argument is not a valid integer */
        if (exitcheck == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return (1);
        }

        info->err_num = _erratoi(info->argv[1]);
        return (-2);
    }

    /* Set the error number and exit status for the default exit case */
    info->err_num = -1;
    return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    /* Get the current working directory */
    s = getcwd(buffer, 1024);
    if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    /* Check if no directory argument is provided */
    if (!info->argv[1])
    {
        /* Get the HOME directory and change to it */
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    /* Check if the directory argument is "-" */
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        /* Check if the OLDPWD environment variable is not set */
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return (1);
        }

        /* Print the OLDPWD directory and change to it */
        _puts(_getenv(info, "OLDPWD=")), _putchar('\n');
        chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
    {
        /* Change to the specified directory */
        chdir_ret = chdir(info->argv[1]);
    }

    /* Handle errors during the chdir operation */
    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]), _eputchar('\n');
    }
    else
    {
        /* Update the OLDPWD and PWD environment variables */
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }

    return (0);
}

/**
 * _myhelp - prints a help message (not yet implemented)
 * @info: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
    char **arg_array;

    /* Temporary workaround to avoid unused variable warning */
    arg_array = info->argv;

    /* Print a message indicating that the help function is not yet implemented */
    _puts("help call works. Function not yet implemented \n");

    /* Temporary workaround to avoid unused variable warning */
    if (0)
        _puts(*arg_array);

    return (0);
}
