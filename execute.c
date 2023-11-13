#include "main.h"

void exec_wa(char *path, char *const *argv)
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

        if (execve(path, argv, NULL) == -1)
        {
            perror("Command not found\n");
            _exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
    }
}