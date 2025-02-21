#include <stdio.h>
#include <string.h>
#include "redirection.h"

char* check_redirection(char **args, int arg_count) {
    char *outfile = NULL;
    for (int i = 0; i < arg_count; i++) {
        if (strcmp(args[i], ">") == 0) {
            // Ensure there's a filename after ">"
            if (args[i+1] == NULL) {
                fprintf(stderr, "Error: no output file specified for redirection.\n");
                return NULL;
            }
            outfile = args[i+1];
            // Remove the ">" operator (and optionally the filename) from the args list.
            // Here, we simply terminate the args list at this position.
            args[i] = NULL;
            break;
        }
    }
    return outfile;
}