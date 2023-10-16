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
    __pid_t pid;

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
    }

    return (0);
}