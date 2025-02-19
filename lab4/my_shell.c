#include <stdio.h>
#include <string.h>
#include "my_fgets.h"
#include "exe_cmd.h"  


int main() {
    char input[100];  // Buffer

    while (1) {
        printf("my_shell> ");  // Display prompt
        my_fgets(input, sizeof(input));  // Read input 

        if (strlen(input) == 0) continue;  // Empty string base case, ignore

        exe_cmd(input);  // Run the command
    }

    return 0;
}