#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "exe_cmd.h"

int builtin_cmd(char *args[]) {
    if (args[0] == NULL) {
        return 0;  // Empty input, base case
    }

    // 'cd' cmd
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            printf("cd: missing arguments\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
        return 1;  // indicator 
    }

    // 'exit' cmd
    if (strcmp(args[0], "exit") == 0) { 
        printf("Exiting shell... \n");
        exit(0);
    }

    return 0;
}

void exe_cmd(char *input) {
    char *args[100];
    int i = 0;

    // Tokenize user input into command + args
    char *token = strtok(input, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  // NULL-terminate empty list

    if (args[0] == NULL) return;  // Ignore empty input

    if (builtin_cmd(args)) {
        return;  // If built-in, execute and return (no forking)
    }

    // Fork a child process
    pid_t pid = fork();  // Process ID = pid

    if (pid == 0) {  // Child process
        execvp(args[0], args);
        perror("Error executing command");  // If execvp fails
        exit(1);
    }   else if (pid > 0) {  // Parent process
        waitpid(pid, NULL, 0);  // Wait for child to finish
    }   else {
        perror("Fork Failed");
    }
}