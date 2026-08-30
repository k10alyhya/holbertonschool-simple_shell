#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

extern char **environ;

void execute_command(char *line, char *program_name);
void print_error(char *prog, char *cmd);
int handle_builtin(char **args, char *line, int *last_status);
void run_command(char **args, char *path, char *line, int *last_status);
char *trim_spaces(char *line);
char *build_full_path(char *dir, char *command);
char *_getenv(const char *name);
char *get_path(char *command);

#endif
