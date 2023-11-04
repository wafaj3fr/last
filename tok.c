#include "main.h"

char *arr[1024];
char **tok(char *line)
{
    char *token;
    char *delim = " ";
    int i;

    token = strtok(line, delim);

    while (token != NULL)
    {
        printf("Token: %s\n", token);
        for (i = 0; arr[i]; i++)
        {
            arr[i] = token;
        }
        token = strtok(NULL, delim);
    }

    return arr;
}