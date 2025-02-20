#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define DEFAULT_TIME_LIMIT 5
pid_t child_pid;

void handle_alarm(int sig) {
    printf("Received signal: %d\n", sig);  // Log the received signal
    if (child_pid > 0) {
        kill(child_pid, SIGKILL);
        printf("Child process timed out and was terminated.\n");
    }
}


void execute(char *command, int default_time_limit) {
    char *args[100];  // child's command-line arguments
    int arg_count = 0;  // child's number of CLAs
    int time_limit = default_time_limit;  // may change later
    
    // Remove newline if present
    command[strcspn(command, "\n")] = 0;
    
    // Tokenize the command
    char *token = strtok(command, " ");
    
    // Check for empty command
    if (token == NULL) {
        return;
    }
    
    // Check for -t flag and update time_limit if present
    if (strcmp(token, "-t") == 0) {
        token = strtok(NULL, " ");
        if (token != NULL) {
            time_limit = atoi(token);
            token = strtok(NULL, " ");
        }
    }
    
    // Store the executable and arguments
    while (token != NULL && arg_count < 99) {  // Leave room for NULL
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;  // NULL terminate the arguments array
    
    if (arg_count == 0) {
        return;  // No executable provided
    }

    child_pid = fork();  // Fork the process
    
    if (child_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (child_pid == 0) {  // Child process
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {  // Parent process
        signal(SIGALRM, handle_alarm);
        alarm(time_limit);
        
        int status;
        waitpid(child_pid, &status, 0);
        alarm(0);  // Cancel the alarm if child terminates
        
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process terminated by signal %d\n", WTERMSIG(status));
        }
    }
}

int main(int argc, char *argv[]) {
    int default_time_limit = DEFAULT_TIME_LIMIT;
    
    if (argc == 2) {
        default_time_limit = atoi(argv[1]);
    }
    
    char command[1024];  // buffer
    
    while (1) {
        printf("my shell> ");
        fflush(stdout);
        
        if (!fgets(command, sizeof(command), stdin)) {
            break;  // EOF ends the shell
        }
        
        if (!strcmp(command, "quit\n")) {
            break;  // quit ends the shell
        }
        
        execute(command, default_time_limit);
    }
    
    return 0;
}