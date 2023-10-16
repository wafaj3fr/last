#include "main.h"

/**
 * main - Entry point
 * @ac: arguments count
 * @argv: arguments
 * Return: 0 for success
 */

int main(int ac, char **argv)
{
    /*char *prompt_of_us = "The_shell_is_this $";*/
    char *line = NULL, *line_cp = NULL;
    /*const char *delimmeter = " \n";
    int num_pars = 0;
    char *pars;*/
    size_t n = 0;
    ssize_t chread;
    int i;

    (void)ac;

    while (1)
    {

       prompt_of_us();
        chread = getline(&line, &n, stdin);

        if (chread == -1)
        {
            write(1, "\n", 1);
            break;
        }

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

    return (0);
}