#include "main.h"


void prompt_of_us(void)
{
    char *prompt = "the shell is this$ ";
    write(1, prompt, _strlen(prompt));
}