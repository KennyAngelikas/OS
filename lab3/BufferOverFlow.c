#include <stdio.h>
#include <string.h>

int main(void) {
    vulnerableFunction();
    return 0;
}

void vulnerableFunction() {
    char buffer[10];

    printf("Enter some text: ");
    scanf("%s", buffer);

    printf("You entered %s\n", buffer);
}