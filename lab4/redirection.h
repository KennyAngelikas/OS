#ifndef REDIRECTION_H
#define REDIRECTION_H

// Checks for output redirection (">") in the args array.
// If found, returns the output filename and modifies args so that the redirection token is removed.
// Returns NULL if no redirection is specified.
char* check_redirection(char **args, int arg_count);

#endif