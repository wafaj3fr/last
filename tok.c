#include "main.h"

int tok_num(char *line)
{
    char *tok, *sep = " \n";
    int n = 0;

    tok = strtok(line, sep);
    while (tok != NULL)
    {
        n++;
        tok = strtok(NULL, sep);
    }
    return (n);
}

char **tok(char *line, char **argv)
{
    char *line_copy, *token, *delim = " \n\t";
    int i, toknum = 0, n = 0;
    /*char **toks;*/

    toknum = _strlen(line) + 1;
    line_copy = malloc(sizeof(char) * toknum);
    if (line_copy == NULL)
    {
        write(1, "error in allocate memory", _strlen("error in allocate memory"));
        return (NULL);
    }
    _strcpy(line_copy, line);
    n = tok_num(line_copy);
    token = strtok(line, delim);

    while (token != NULL)
    {
        toknum++;
        token = strtok(NULL, delim);
    }
    toknum++;

    argv = (char **)malloc(sizeof(char *) * toknum);
    if (argv == NULL)
    {
        write(1, "tsh: memory allocation error", 28);
        return (NULL);
    }
    for (i = 0; token != NULL; i++)
    {
        argv[i] = malloc(_strlen(token) + 1);
        if (argv[i] == NULL)
        {
            write(1, "tsh: memory allocation error", 28);

            return NULL;
        }

        _strcpy(argv[i], token);
        token = strtok(NULL, delim);
        printf("%s: is a token\n", (char *)argv);
    }

    argv[i] = NULL;
    return argv;
}