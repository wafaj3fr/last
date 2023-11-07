#include "main.h"

/**
 * get_line - get input to shell exec
 *
 * @argv: arg values
 *
 * Return: line readed;
 */

char *get_line(char **argv)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t stread;

	stread = getline(&line, &n, stdin);
	if (stread == -1)
	{
		if (feof(stdin))
		{
			free(line);
			exit(0);
		}
		else
		{
			write(2, argv[0], _strlen(argv[0]));
			write(2, " :can not read input\n", _strlen(" :can not read input\n"));
			free(line);
			return (NULL);
		}
	}

	if (line[stread - 1] == '\n')
		line[stread - 1] = '\0';

	return (line);
}