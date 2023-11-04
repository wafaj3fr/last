#include "main.h"

char *arr[1024];
char **tok(char *line)
{
    char *token;
    char *delim = " \n\t";
    int i, j;

    token = strtok(line, delim);

    for (i = 0; token != NULL; i++)
    {
        arr[i] = malloc(_strlen(token) + 1);
        if (arr[i] == NULL)
        {
            write(1, "tsh: memory allocation error", 28);
            for (j = 0; j < i; j++)
            {
                free(arr[j]);
            }

            return (NULL);
        }

        _strcpy(arr[i], token);
        token = strtok(NULL, delim);
    }
    arr[i] = NULL;
    free(arr[i]);

    printf("%s", *arr);

    return arr;
}