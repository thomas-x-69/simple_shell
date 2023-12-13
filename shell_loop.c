#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);

		// Display prompt if in interactive mode
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);

		// Get user input
		r = get_input(info);

		if (r != -1)
		{
			set_info(info, av);

			// Check for and execute built-in commands
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');

		// Free allocated memory
		free_info(info, 0);
	}

	// Write command history to file and free remaining memory
	write_history(info);
	free_info(info, 1);

	// Exit with status code in non-interactive mode
	if (!interactive(info) && info->status)
		exit(info->status);

	// Handle exit due to built-in command
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}

	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *        -2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	// Iterate through the built-in command table
	for (i = 0; builtintbl[i].type; i++)
	{
		// Check if the input command matches a built-in command
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;

			// Execute the built-in command function
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	}

	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];

	// Count the number of non-delimiter characters in the command
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;

	// If no non-delimiter characters, return
	if (!k)
		return;

	// Find the command in the PATH environment variable
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		// Check if the command is an executable in the current directory
		if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	// Fork a child process
	child_pid = fork();
	if (child_pid == -1)
	{
		// TODO: Error handling
		perror("Error:");
		return;
	}

	// Code executed by the child process
	if (child_pid == 0)
	{
		// Execute the command using execve
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			// Handle execution failure
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		// TODO: Error handling
	}
	// Code executed by the parent process
	else
	{
		// Wait for the child process to finish
		wait(&(info->status));

		// Check if the child process terminated normally
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
