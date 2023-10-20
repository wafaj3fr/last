#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strcmp(const char *s1, const char *s2);
char *_getenv(const char *name);

char *search_directories(const char *command, const char *path);
char *allocate_full_path(const char *dir, const char *command);
char *check_access_and_return(const char *full_path);
char **tokenize(const char *str, const char *delim, int *num_tokens);
int count_tokens(const char *str, const char *delim);
int is_empty_line(const char *line);
int is_env_command(const char *line);
void print_environment();
char *_getenv(const char *name);

void dollar_prpmpt() {
	char *prompt = "$ ";
	write(1, prompt, _strlen(prompt));
}

int is_exit_command(const char *line) {
	return _strcmp(line, "exit") == 0;
}

char *_getenv(const char *name)
{
	// Get the environment variables.
	extern char **environ;

	// Iterate over the environment variables and find the one with the specified name.
	for (int i = 0; environ[i] != NULL; i++) {
		char *key = strtok(environ[i], "=");
		char *value = strtok(NULL, "");
		if (strcmp(key, name) == 0) {
			return value;
		}
	}

	// If the environment variable is not found, return NULL.
	return NULL;
}
void execute(char *const *argv, const char *path) {
	if (execve(path, argv, NULL) == -1) {
		perror("Error:");
	}
}
char *check_access_and_return(const char *full_path) {
	if (access(full_path, X_OK) == 0) {
		return strdup(full_path);  // Return a duplicate of the full path
	} else {
		return NULL;  // Access denied or file not found
	}
}
char *search_directories(const char *command, const char *path) {
	char *path_copy = strdup(path);
	if (path_copy == NULL)
		return NULL;

	char *dir = strtok(path_copy, ":");
	char *full_path = NULL;

	while (dir != NULL) {
		full_path = allocate_full_path(dir, command);
		if (full_path != NULL) {
			char *accessed_path = check_access_and_return(full_path);
			free(full_path);
			if (accessed_path != NULL) {
				free(path_copy);
				return accessed_path;
			}
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return NULL;
}

char *allocate_full_path(const char *dir, const char *command) {
	size_t max_path_length = 1024;  // Adjust as needed
	char *full_path = malloc(max_path_length);

	if (full_path == NULL) {
		return NULL;  // Allocation error
	}

	snprintf(full_path, max_path_length, "%s/%s", dir, command);

	if (strlen(full_path) >= max_path_length) {
		// The path is too long, reallocate and try again
		free(full_path);
		max_path_length *= 2;
		full_path = malloc(max_path_length);

		if (full_path == NULL) {
			return NULL;  // Reallocation error
		}

		snprintf(full_path, max_path_length, "%s/%s", dir, command);
	}

	return full_path;
}

void exit_builtin() {
	write(1, "\n", 1);
	exit(0);
}
int is_env_command(const char *line) {
	return _strcmp(line, "env") == 0;
}

int is_empty_line(const char *line) {
	for (int i = 0; line[i] != '\0'; i++) {
		if (!isspace((unsigned char)line[i])) {
			return 0;  // Line is not empty
		}
	}
	return 1;  // Line is empty
}
int count_tokens(const char *str, const char *delim) {
	char *str_copy = strdup(str);
	if (str_copy == NULL) {
		return -1;  // Allocation error
	}

	char *token;
	int count = 0;

	token = strtok(str_copy, delim);
	while (token != NULL) {
		count++;
		token = strtok(NULL, delim);
	}

	free(str_copy);
	return count;
}
char **tokenize(const char *str, const char *delim, int *num_tokens) {
	// Create a copy of the input string to avoid modifying the original
	char *str_copy = strdup(str);
	if (str_copy == NULL) {
		return NULL;  // Allocation error
	}

	// Tokenize the string
	char *token;
	char **tokens = NULL;
	int max_tokens = 10;  // Adjust as needed
	int count = 0;

	tokens = (char **)malloc(max_tokens * sizeof(char *));
	if (tokens == NULL) {
		free(str_copy);
		return NULL;  // Allocation error
	}

	token = strtok(str_copy, delim);
	while (token != NULL) {
		tokens[count] = strdup(token);
		if (tokens[count] == NULL) {
			// Allocation error, clean up and return NULL
			for (int i = 0; i < count; i++) {
				free(tokens[i]);
			}
			free(tokens);
			free(str_copy);
			return NULL;
		}

		count++;
		if (count >= max_tokens) {
			max_tokens *= 2;
			tokens = (char **)realloc(tokens, max_tokens * sizeof(char *));
			if (tokens == NULL) {
				// Reallocation error, clean up and return NULL
				for (int i = 0; i < count; i++) {
					free(tokens[i]);
				}
				free(tokens);
				free(str_copy);
				return NULL;
			}
		}

		token = strtok(NULL, delim);
	}

	*num_tokens = count;
	free(str_copy);
	return tokens;
}
void free_resources(char *line, char *backup_line, char *pathval, char **argv) {
	if (line != NULL)
		free(line);
	if (backup_line != NULL)
		free(backup_line);
	if (pathval != NULL)
		free(pathval);
	if (argv != NULL) {
		for (int i = 0; argv[i] != NULL; i++) {
			free(argv[i]);
		}
		free(argv);
	}
}

char *find_exe(const char *line) {
	char *path = _getenv("PATH");
	if (path == NULL) {
		return NULL;
	}

	return search_directories(line, path);
}

void execute_command(char *line, char *backup_line, char **argv) {
	int status;
	pid_t pid;
	char *pathval;

	pathval = find_exe(line);

	if (access(pathval, X_OK) == 0) {
		pid = fork();

		if (pid == -1) {
			perror("fork");
			free_resources(line, backup_line, pathval, argv);
			exit(-1);
		} else if (pid == 0) {
			execute(argv, pathval);
			free_resources(line, backup_line, pathval, argv);
			exit(0);
		} else {
			wait(&status);
		}
	} else {
		write(1, "Command not found\n", 19);
	}
}

void read_and_backup_line(char **line, char **backup_line, size_t *n) {
	ssize_t stread;

	stread = getline(line, n, stdin);
	if (stread == EOF) {
		write(1, "\n", 1);
		exit(0);
	}

	*backup_line = strdup(*line);
	if (*backup_line == NULL) {
		write(1, "tsh: memory allocation error", 28);
		exit(-1);
	}
}

/**
 * _strlen - returns the length of a string.
 * @s: string to be calculated
 * Return: length of the string
 */

int _strlen(char *s)
{
	int len = 0;
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		len++;
	}

	return (len);
}

/**
 * _strcat - concatenates two strings.
 * @dest: string to be expanded by the other string
 * @src: string to be added to string dest
 * Return: a pointer to the resulting string dest
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}

	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - compare 2 strings.
 * @s1: string to be compared.
 * @s2: string for comparation.
 * Return: Difference.
 */
int _strcmp(const char *s1, const char *s2)
{
	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
	{
		return (0);
	}
	else
	{
		return (*s1 - *s2);
	}
}

/**
 * *_strcpy - copies the string pointed to by src
 * including the terminating null byte (\0)
 * to the buffer pointed to by dest
 * @dest: pointer to the buffer in which we copy the string
 * @src: string to be copied
 *
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int len, i;

	len = 0;

	while (src[len] != '\0')
	{
		len++;
	}

	for (i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strdup - Entry point
 *@str: string we need to duplicate
 * Return: a pointer to the duplicated string or NULL
 */

char *_strdup(char *str)
{
	char *strnew = NULL;
	unsigned int i;
	int n;

	if (str == NULL)
		return (NULL);
	for (n = 0; str[n] != '\0'; n++)
		;
	strnew = (char *)malloc(n + 1 * sizeof(char));
	if (strnew != NULL)
	{
		for (i = 0; str[i] != '\0'; i++)
			strnew[i] = str[i];
	}
	else
	{
		return (NULL);
	}
	strnew[i] = '\0';
	return (strnew);
}


void print_environment()
{
	extern char **environ;

	char **env = environ;
	while (*env) {
		write(1, *env, _strlen(*env));
		write(1, "\n", 2);
		env++;
	}
}

int main(int ac, char **argv) {
	char *line = NULL, *backup_line = NULL;
	size_t n = 0;
	const char *delim = " \n";
	int num_pars;

	(void)ac;

	while (1) {
		num_pars = 0;
		dollar_prpmpt();

		read_and_backup_line(&line, &backup_line, &n);

		num_pars = count_tokens(backup_line, delim);
		char **argv = tokenize(backup_line, delim, &num_pars);

		if (is_exit_command(line)) {
			free_resources(line, backup_line, NULL, argv);
			exit(0);
		} else if (is_empty_line(line)) {
			continue;
		} else if (is_env_command(line)) {
			print_environment();
		}

		execute_command(line, backup_line, argv);

		free_resources(line, backup_line, NULL, argv);
	}

	return (0);
}
