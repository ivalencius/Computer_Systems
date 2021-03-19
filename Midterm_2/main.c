// Author: Ilan Valencius
// Email: valencig@bc.edu

// Packages
#include <stdio.h>
#include <stdlib.h>

// Files
#include "multiply.c"

// Tales input of 2 numbers and calls multiply() and prints output.
int main(void) {
    long a, b, result;
    printf("> ");
    while (scanf("%ld %ld", &a, &b) != 0) {
        result = multiply(a, b);
        printf("%ld * %ld = %ld",a,b,result);
        printf("\n> ");
    }
    return EXIT_SUCCESS;
}
