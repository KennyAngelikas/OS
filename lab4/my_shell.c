#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_fgets.h"
#include "exe_cmd.h"  

int main() {
    char *input = NULL;  // Pointer to store input
    size_t len = 0;  // Size of allocated memory

    while (1) {
        printf("my_shell> ");  // Display prompt
        size_t read = getline(&input, &len, stdin);  // Dynamically alloc memory
        
        if (read == -1) {  // Handle EOF
            printf("\nExiting shell...\n");
            break;
        }
        
        input[strcspn(input, "\n")] = '\0';  // remove newline bc getline() adds newline

        if (strlen(input) == 0) continue;  // Empty string base case, ignore

        exe_cmd(input);  // Run the command
    }

    free(input);  // Free alloc memory
    return 0;
}