#include "main.h"

void parse(char *line, ssize_t chread)
{

    char *line_cp;
    char *pars;

    line_cp = malloc(chread);

    if (line_cp == NULL)
    {
        write(1, "tsh: memory allocation error", 28);
        return (-1);
    }

    for (i = 0; argv[i]; i++)
    {
        write(1, argv[i], _strlen(argv[i]));
        write(1, ": No such file or directory\n", 28);
    }
}