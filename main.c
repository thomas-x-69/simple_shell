#include "shell.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	// Initialize an array of 'info_t' structures with a single initialized element
	info_t info[] = { INFO_INIT };
	int fd = 2;

	// Inline assembly to modify 'fd'
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	// Check if there is a command-line argument
	if (ac == 2)
	{
		// Open the specified file in read-only mode
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			// Handle file open errors
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd; // Set the 'readfd' field in the 'info' structure
	}

	// Populate environment variables list
	populate_env_list(info);

	// Read history from file
	read_history(info);

	// Start the shell
	hsh(info, av);

	// Return success
	return (EXIT_SUCCESS);
}
