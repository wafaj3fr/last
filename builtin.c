#include "main.h"

int built_in(char **toks, char **env)
{
    if (_strcmp(toks[0], "env") == 0)
    {
        print_environment(env);
        return (1);
    }

    else if (_strcmp(toks[0], "exit") == 0)
    {
        return (1);
    }

    return (0);
}