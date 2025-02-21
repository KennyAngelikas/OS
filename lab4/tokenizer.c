#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

// A better tokenizer should detect quotes (" or ') and keep words together.

void tokenize_input(char *input, char *args[], int *arg_count) {
    *arg_count = 0;  // Reset argument count

    // Tokenize user input into arguments
    char *token = strtok(input, " ");  // strtok replaces spaces with \0 (null terminators)
    while (token != NULL) {
        args[(*arg_count)++] = token;
        token = strtok(NULL, " ");
    }
    args[*arg_count] = NULL;  // NULL-terminate argument list
}
