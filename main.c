#include "main.h"

/**
 * main - Entry point
 * @ac: arguments count
 * @argv: arguments
 * Return: 0 for success
 */

int main(int ac, char **argv)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t stread;
    char *path;

    (void)ac;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(1, "$ ", 2);
        stread = getline(&line, &n, stdin);
        if (stread == EOF)
            return (-1);

        argv = tok(line);
        path = argv[0];
        execve(path, argv, NULL);
    }
    return (0);
}