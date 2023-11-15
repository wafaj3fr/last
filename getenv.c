#include "main.h"

/**
 * _getenv - gets the environment variable path.
 * @name: name of the env.
 */

char *_getenv(char **env, char *name)
{
    int i = 0;

    for (i = 0; env[i]; i++)
    {
        if (_strcmp(name, env[i]) == 0)
            return (env[i]);
    }

    return (NULL);
}

/**
 * print_environment - prints environment variables
 * @env: environment
 */

void print_environment(char **env)
{
    char **envp = env;

    while (*envp != NULL)
    {
        write(1, *envp, _strlen(*envp));
        write(1, "\n", 1);
        envp++;
    }
}