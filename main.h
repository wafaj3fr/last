#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int _strlen(char *s);
void parse(char *line, ssize_t chread);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strcmp(const char *s1, const char *s2);
void prompt_of_us(void);

#endif