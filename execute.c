#include "main.h"

void exec_wa(char *path, char *const *argv)
{
    execve(path, argv, NULL);
}