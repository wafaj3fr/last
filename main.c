#include "main.h"

/**
 * main - Entry point
 * @ac: arguments count
 * @argv: arguments
 * Return: 0 for success
 */

int main(int ac, char **argv, char **env)
{
    char *command = NULL;
    char **toks;
    int z = 0;
    /*char *path;*/

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

        if (_strcmp(command, "env") == 0)
        {
            print_environment();
            z = 1;
            continue;
        }

        if (_strcmp(command, "exit") == 0)
        {
            z = 1;
            break;
        }

        z = 0;

        free(command);

        if (z == 0)
            exec_wa(toks[0], toks, env);

        _free(toks);
    }
    if (command != NULL)
        free(command);

    if (toks != NULL)
        _free(toks);

    return (0);
}
