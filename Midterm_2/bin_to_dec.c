#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 33
#define USAGE "Please enter a binary integer to print out as an unsigned decimal number, or \"q\" to quit.\n"

unsigned int bin_to_dec(char * input) {
    unsigned int value = 0u;
    while (*input) {
        value *= 2;
        value += *input - '0';
        ++input;
    }
    return value;
}

/*
int main(void) {
    char input[MAX_INPUT_SIZE];
    puts(USAGE);
    fputs("> ", stdout);
    while (scanf("%s", input) != EOF && strcmp(input, "q")) {
        unsigned int dec = bin_to_dec(input);
        printf("%u\n", dec);
        fputs("> ", stdout);
    }
    return EXIT_SUCCESS;
}
*/
