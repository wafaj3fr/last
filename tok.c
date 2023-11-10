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
    char *line_copy, *token, *delim = " \n\t";
    int i = 0, toknum = 0;
    char **toks = NULL;

    toknum = _strlen(line) + 1;
    line_copy = malloc(sizeof(char) * toknum);
    if (line_copy == NULL)
    {
        write(1, "error in allocate memory", _strlen("error in allocate memory"));
        return (NULL);
    }
    _strcpy(line_copy, line);
    toknum = tok_num(line_copy);

    toks = malloc((toknum + 1) * sizeof(char *));
    if (toks == NULL)
        return (NULL);

    token = strtok(line, delim);
    while (token != NULL)
    {
        toks[i] = malloc((_strlen(token) + 1) * sizeof(char));
        if (toks == NULL)
        {
            _free(toks);
            return (NULL);
        }
        _strcpy(toks[i], token);
        token = strtok(NULL, delim);
        i++;
    }
    toks[toknum] = NULL;
    return (toks);
}