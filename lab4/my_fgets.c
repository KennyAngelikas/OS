#include <stdio.h>
#include "my_fgets.h"

void my_fgets(char *buffer, int size) {
    int i = 0;
    char ch;

    while (i < size - 1) {
        ch  = getchar();

        if (ch == '\n' || ch == EOF) {
            buffer[i] = '\0';
            return;
        }

        buffer[i] = ch;
        i++;
    }

    buffer[i] ='\0'; 
}