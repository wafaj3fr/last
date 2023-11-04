#include "main.h"

char *arr[1024];
char **tok(char *line)
{
    char *token;
    char *delim = " ";
    int i;

    token = strtok(line, delim);

        for (i = 0; token != NULL; i++)
        {
            arr[i] = malloc(_strlen(token) + 1);
            if (arr[i] == NULL)
            {
                write(1, "tsh: memory allocation error", 28);
                break;;
            }

            _strcpy(arr[i], token);
            token = strtok(NULL, delim);
        }
        arr[i] = NULL;

    printf("%s", *arr);

    return arr;
}