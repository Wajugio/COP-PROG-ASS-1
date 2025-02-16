#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define DEFAULT_TIME_LIMIT 5

// Function declarations
void handle_alarm(int sig);
void execute(char *command, int default_time_limit);

// Global variables
extern pid_t child_pid;

#endif /* SHELL_H */