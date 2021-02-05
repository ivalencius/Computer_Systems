/*
* Author: Ilan Valencius - valencig@bc.edu
*/

#include <stdio.h>
#include <stdlib.h>

double convert(double celcius) {
    return ((celcius * 9) / (double) 5) + 32;
}

int main(int argc, char *argv[]) {
    if (argc == 1)
        return 0;
    double celcius = strtod(argv[1], NULL);
    double fahrenheit = convert(celcius);
    printf("Fahrenheit:%.2f\n", fahrenheit);
    return 0;
}

