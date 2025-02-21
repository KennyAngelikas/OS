#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "exe_cmd.h"
#include "builtin.h"
#include "tokenizer.h"
#include "pipe_handler.h"
#include "redirection.h"

void exe_cmd(char *input) {
    char *args[100];
    int arg_count;

    // Use tokenizer to split input into arguments
    tokenize_input(input, args, &arg_count);

    if (args[0] == NULL) return;  // Ignore empty input, Base case

    // Check for pipes
    int pipe_index = -1;
    for (int i = 0; i < arg_count; i++) {
        if (strcmp(args[i], "|") == 0) {
            pipe_index = i;
            break;
        }
    }

    if (pipe_index != -1) {
        pipe_handler(args, pipe_index);
        return;
    }

    // Call the redirection function to check for output redirection.
    char *outfile = check_redirection(args, arg_count);

    // Check for built-in commands
    if (builtin(args)) {
        return;  // If built-in, execute and return (no forking)
    }

    // Fork a child process for external commands

    // Fork for external commands.
    pid_t pid = fork();
    if (pid == 0) {  // Child process
        if (outfile != NULL) {
            int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            if (dup2(fd, STDOUT_FILENO) < 0) {  // Redirect stdout to file
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(fd);
        }

        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork failed");
    } else {
        waitpid(pid, NULL, 0);
    }
}