#include "main.h"

void exec_wa(char *const *argv)
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child_pid == 0)
    {
        char path[256];

        char *args[] = {argv, NULL};
        execve(path, args, NULL);

        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
    }
}