#include "main.h"


void prompt_of_us(void)
{
    char *prompt = "wash$ ";
    write(1, prompt, _strlen(prompt));
}