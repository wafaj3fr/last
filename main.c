#include "main.h"

/**
 * main - Entry point
 * @ac: arguments count
 * @argv: arguments
 * Return: 0 for success
 */

int main(int ac, char **argv)
{
    char *command = NULL;
    /*char **toks;*/
    /*char *path;*/

    (void)ac;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(1, "$ ", 2);

        command = get_line(argv);
        if (command == NULL)
            continue;

        argv = tok(command);
        if (argv == NULL)
        {
            free(command);
            continue;
        }

        free(command);

        /*exec_wa(argv[0], (char *const *)argv);*/

        _free(argv);
    }

    if (command != NULL)
        free(command);

    if (argv != NULL)
        _free(argv);

    return (0);
}
