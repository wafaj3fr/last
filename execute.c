#include "main.h"

void exec_wa(char *path, char *const *argv, char **env)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
    }
    else if (pid == 0)
    {

        if (execve(path, argv, env) == -1)
        {
            perror("execve");
            _exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
    }
}