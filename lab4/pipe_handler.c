#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "pipe_handler.h"
#include "builtin.h"

void pipe_handler(char **args, int pipe_index) {
    // 1. Split args into left_cmd and right_cmd
    args[pipe_index] = NULL;              // Replace '|' with NULL
    char **left_cmd  = args;              // left side starts at args[0]
    char **right_cmd = &args[pipe_index+1]; // right side starts after '|'

    // 2. Create the pipe
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return;
    }

    // 3. Fork for the left command
    pid_t pid1 = fork();
    if (pid1 == 0) {
        // Child 1: redirect STDOUT -> fd[1]
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        // If left_cmd is builtin, run it in child
        if (builtin(left_cmd)) {
            exit(EXIT_SUCCESS);
        } else {
            execvp(left_cmd[0], left_cmd);
            perror("execvp (left_cmd)");
            exit(EXIT_FAILURE);
        }
    } else if (pid1 < 0) {
        perror("fork (left_cmd)");
        return;
    }

    // 4. Fork for the right command
    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Child 2: redirect STDIN -> fd[0]
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);

        // If right_cmd is builtin, run it in child
        if (builtin(right_cmd)) {
            exit(EXIT_SUCCESS);
        } else {
            execvp(right_cmd[0], right_cmd);
            perror("execvp (right_cmd)");
            exit(EXIT_FAILURE);
        }
    } else if (pid2 < 0) {
        perror("fork (right_cmd)");
        return;
    }

    // 5. Parent: close pipe ends and wait
    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}