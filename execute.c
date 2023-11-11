#include "main.h"

void exec_wa(char *path, char *const *argv)
{
    pid_t pid;
    int status;
    char **new_argv;
    size_t full_path_len = strlen(path) + 1;
    char *full_path = malloc(full_path_len);

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        strcpy(full_path, path);

        new_argv = malloc((sizeof(char *) * 2));
        new_argv[0] = full_path;
        new_argv[1] = NULL;

        if (execve(path, argv, NULL) == -1)
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