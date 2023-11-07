#include "main.h"

/**
 * main - Entry point
 * @ac: arguments count
 * @argv: arguments
 * Return: 0 for success
 */

int main(int ac, char **argv)
{
    char *command, *toks, *path;

    (void)ac;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(1, "$ ", 2);

        command = get_line(argv);
        if (command == NULL)
            continue;

        toks = tok(command);
        if (toks == NULL)
        {
            free(command);
            continue;
        }
        free(command);

        exec_wa(path, argv);

        free_arr(toks);
    }

    if (command != NULL)
        free(command);

    if (toks != NULL)
        free_arr(toks);

    return (0);
}
