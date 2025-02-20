#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

void tokenize_input(char *input, char *args[], int *arg_count) {
    *arg_count = 0;  // Reset argument count

    // Tokenize user input into arguments
    char *token = strtok(input, " ");
    while (token != NULL) {
        args[(*arg_count)++] = token;
        token = strtok(NULL, " ");
    }
    args[*arg_count] = NULL;  // NULL-terminate argument list
}
