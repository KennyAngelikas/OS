#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"

/*
✔ Ensures functions are used correctly (return type, parameters).
✔ Prevents implicit declaration errors.
✔ Allows calling functions before defining them.
✔ Makes code more modular, especially in multi-file projects. (.h files)
✔ Does NOT allocate memory or execute anything—it’s just a declaration.
*/

// Function prototypes for built-in commands
int do_cd(char *args[]);
int do_exit(char *args[]);

// Structure to map command names to function pointers
typedef struct {
    const char *name;
    int (*func)(char *args[]);
} builtin_entry;

// Lookup table for built-in commands
builtin_entry builtins[] = {
    {"cd", do_cd},
    {"exit", do_exit}
};

#define NUM_BUILTINS (sizeof(builtins) / sizeof(builtin_entry))

// Implementation of the 'cd' command
int do_cd(char *args[]) {
    if (args[1] == NULL) {
        printf("cd: missing argument\n");
        return 1;
    }

    if (chdir(args[1]) != 0) {
        perror("cd");
        return 1;
    }
    return 1;  // Indicate that a built-in command was executed
}

// Implementation of the 'exit' command
int do_exit(char *args[]) {
    printf("Exiting shell...\n");
    exit(0);
    return 1;  // This line is not reached, but added for consistency
}

// The builtin function now uses the lookup table
int builtin(char *args[]) {
    if (args[0] == NULL) {
        return 0;  // No command entered
    }
    for (int i = 0; i < NUM_BUILTINS; i++) {
        if (strcmp(args[0], builtins[i].name) == 0) {
            return builtins[i].func(args);  // Call the corresponding function
        }
    }
    return 0;  // Command not found among built-ins
}