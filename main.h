#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strcmp(const char *s1, const char *s2);
char **tok(char *command);
void exec_wa(char **path, char **argv, char **env);
char *get_line(char **argv);
int toknum(char *command);
void _free(char **arr);
char *_getenv(char **env, char *name);
void print_environment(char **env);
int get_path(char **tokens, char **env);
int built_in(char **toks, char **env);

#endif