/*
* Author: Ilan Valencius - valencig@bc.edu
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SUCCESS == 0 so need '!(fxn)' for correct if statements 
#define ERROR 1
#define SUCCESS 0

// Checks whether 'c' is a digit 0-9.
int is_digit(char c) {
    if (!((c>='0')&&(c<='9')))
        return SUCCESS;
    else
        return ERROR;
}

// Checks whether the input string is floating point number (must contain ".")
int is_floating_point_number(char* input){
    // c refers to the first character in the string "input".
    char c = *input;
    // Checks if first char is either a digit or '+'/'-'.
    if (!(is_digit(c) || c == '+') || (c == '-'))
        return ERROR;
    // Indicates the presence of the required '.' in the string.
    bool dot = false;
    for(int i = 1; input[i] !=0; i++) {
        c = input[i];
        if (c == '.') {
            // If one '.' already found, return ERROR.
            if (dot)
                return ERROR;
            else
                dot = true;
            continue;
        }
        // If not a digit, return ERROR.
        else if (!is_digit(c))
            return ERROR;
    }
    return (dot ? SUCCESS : ERROR);
}

// Checks if the string is an integer starting with '-'/'+' and containing all numerals.
int is_integer(char* input){
     // c refers to the first character in the string "input".
    char c = *input;
    // Checks if first char is either a digit or '+'/'-'.
    if (!(is_digit(c) || (c == '+') || (c == '-')))
        return ERROR;
    for(int i = 1; input[i] !=0; i++) {
        // If not a digit, return ERROR.
        c = input[i];
        if (is_digit(c) == SUCCESS)
            return ERROR;
    }
    return SUCCESS;
}

// Checks if string ends in 'C' or 'F' then stores the string as a double in &temperature.
int validate_and_parse_input(char * input, double * temperature, char * scale) {
    int length = strlen(input);
    // Determine if terminating char is 'C' or 'F'
    char terminator = input[length-1];
    if (terminator == 'C' || terminator == 'F')
        *scale = terminator;
    else 
        return ERROR;
    // Replace terminating char with '\0' (need to make new string)
    char input_copy[length+1];
    strcpy(input_copy, input); 
    input_copy[length-1] = '\0';
    // Check if floating point
    if (is_floating_point_number(input_copy) == SUCCESS)
        *temperature = strtod(input_copy, NULL);
    else if (is_integer(input_copy) == SUCCESS)
        *temperature = (double)atoi(input_copy);
    else 
        return ERROR;
    return SUCCESS;

}

// Converts celcius to fahrenheit.
double celsius_to_farenheit(double celsius) {
    return ((celsius * 9) / (double) 5) + 32;
}

// Converts fahrenheit to celcius.
double fahrenheit_to_celsius(double fahrenheit) {
    return (fahrenheit - 32) * 5 / (double) 9;
}

// Prints error message for bad input.
void print_usage() {
    printf("\nERROR: PLEASE ENTER INPUT IN VALID FORMAT\n");
}

// Prints correct output based on cases from validate_and_parse
void print_output(double celsius, double fahrenheit, char scale) {
    if (scale == 'C')
        printf("\nCelsius: %f | Fahrenheit: %f\n", celsius, fahrenheit);
    else if (scale == 'F')
        printf("\nFahrenheit: %f | Celsius: %f\n", fahrenheit, celsius);
    else
        printf("INTERNAL ERROR: SCALE IMPROPER VALUE");
}

// Gets input and organizes function calls
int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage();
        return 0;
    }
    else {
        double temperature;
        char scale;
        char* input = argv[1];
        int result = validate_and_parse_input(input, &temperature, &scale);
        if(result == ERROR) {
            print_usage();
            return 0;
        }
        else {
            printf("%c",scale);
            if (scale == 'C')
                print_output(temperature,celsius_to_farenheit(temperature), scale);
            else
                print_output(fahrenheit_to_celsius(temperature), temperature,scale);
            return 0;
        }

    }
}