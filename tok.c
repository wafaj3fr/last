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

char **tok(char *line)
{
    char *token, *delim = " \n\t";
    int i = 0, n_toks = 0;
    char **arr_toks = NULL;
    char *line_copy;

    if (line == NULL || *line == '\0')
    {
        return (NULL);
    }

    n_toks = _strlen(line) + 1;
    line_copy = malloc(n_toks * (sizeof(char)));
    if (line_copy == NULL)
    {
        write(2, "Error: Memory allocation failed\n", _strlen("Error: Memory allocation failed\n"));
        return (NULL);
    }
    _strcpy(line_copy, line);
    n_toks = tok_num(line_copy);
    free(line_copy);

    arr_toks = malloc((n_toks + 1) * sizeof(char *));
    if (arr_toks == NULL)
    {
        write(2, "Error: Memory allocation failed\n", _strlen("Error: Memory allocation failed\n"));
        return (NULL);
    }

    token = strtok(line, delim);
    while (token != NULL)
    {
        arr_toks[i] = malloc((_strlen(token) + 1) * sizeof(char));
        if (arr_toks == NULL)
        {
            _free(arr_toks);
            write(2, "Error: Memory allocation failed\n", _strlen("Error: Memory allocation failed\n"));
            return (NULL);
        }
        _strcpy(arr_toks[i], token);
        token = strtok(NULL, delim);
        i++;
    }
    arr_toks[n_toks] = NULL;

    return (arr_toks);
}