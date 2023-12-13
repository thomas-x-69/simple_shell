#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info; // Unused parameter (prevents compiler warnings)
	
	// Check if the path is valid and obtain file information
	if (!path || stat(path, &st))
		return (0);

	// Check if the file has regular file type
	if (st.st_mode & S_IFREG)
	{
		return (1); // Return 1 if the file is an executable command
	}
	return (0); // Return 0 if the file is not an executable command
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024]; // Static buffer to hold duplicated characters
	int i = 0, k = 0;

	// Copy characters from pathstr[start] to pathstr[stop-1] into buf
	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0; // Null-terminate the buffer
	return (buf); // Return a pointer to the duplicated buffer
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	// Check if the cmd starts with "./" and is a valid executable
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	// Iterate through the PATH string and try to find the cmd
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			// Create a path by duplicating characters between curr_pos and i
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			// Check if the constructed path is a valid executable
			if (is_cmd(info, path))
				return (path);

			// Break if the end of the PATH string is reached
			if (!pathstr[i])
				break;

			curr_pos = i; // Update curr_pos for the next iteration
		}
		i++;
	}
	return (NULL); // Return NULL if the cmd is not found in the PATH
}
