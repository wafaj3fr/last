#include "main.h"

/**
 * main - Entry point
 * @ac: arguments count
 * @argv: arguments
 * Return: 0 for success
 */

int main(int ac, char **argv)
{
    int i;
    char *command = NULL, **toks = NULL;
    /*char *path;*/

    (void)ac;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(1, "$ ", 2);

        command = get_line(argv);
        if (command == NULL)
            continue;

        toks = tok(command, argv);
        printf("%s", (char *)toks);
        if (toks == NULL)
        {
            free(command);
            continue;
        }
        for (i = 0; toks[i] != NULL; i++)
        {
            printf("%s", toks[i]);
            printf("THE SHELL");
        }

        free(command);

        exec_wa(toks[0], (char *const *)toks);

        _free(toks);
    }

    if (command != NULL)
        free(command);

    if (toks != NULL)
        _free(toks);

    return (0);
}
