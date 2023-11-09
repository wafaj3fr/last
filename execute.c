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
        execve(path, argv, NULL);
    }
    else
    {
        wait(&status);
    }
}