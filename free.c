#include "main.h"

void _free(char **arr)
{
    int i;

    if (arr == NULL)
        return;

    for (i = 0; arr[i] != NULL; i++)
    {
        free(arr[i]);
    }
    free(arr);
}