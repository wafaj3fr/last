#include "main.h"

/**
 * get_line - get input to shell exec
 *
 * @av: arg values
 *
 * Return: line readed;
 */

char *get_line(char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t chread;

	nread =  getline(&line, &len, stdin);
	if (chread == -1)
	{
		if (feof(stdin))
		{
			free(line);
			exit(0);
		}
		else
		{
			_print(2, av, " :can not read input\n");
			free(line);
			return (NULL);
		}
	}

	if (line[chread - 1] == '\n')
		line[chread - 1] = '\0';

	return (line);
}