#include "main.h"

void exec_wa(char **path, char **argv, char **env)
{
    pid_t pid;
    int status;
    if (path == NULL)
    {
        return;
    }

    /*if (path[0][0] != '.' && path[0][0] != '/')
    {
        if (built_in(path, env))
            return;
        else if (!get_path(path, env))
        {
            return;
        }
    }*/
    else
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
        }
        else if (pid == 0)
        {

            if (execve(path[0], argv, env) == -1)
            {
                perror("execve Error");
                _exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(&status);
        }
    }
}