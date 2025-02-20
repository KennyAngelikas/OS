#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "exe_cmd.h"
#include "builtin.h"
#include "tokenizer.h"

void exe_cmd(char *input) {
    char *args[100];
    int arg_count;

    // Use tokenizer to split input into arguments
    tokenize_input(input, args, &arg_count);

    if (args[0] == NULL) return;  // Ignore empty input

    // Check for built-in commands
    if (builtin(args)) {
        return;  // If built-in, execute and return (no forking)
    }

    // Fork a child process for external commands
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        execvp(args[0], args);
        perror("Error executing command");  // If execvp fails
        exit(1);
    } else if (pid > 0) {  // Parent process
        waitpid(pid, NULL, 0);  // Wait for child to finish
    } else {
        perror("Fork failed");
    }
}
