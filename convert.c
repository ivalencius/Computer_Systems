/*
* Author: Ilan Valencius - valencig@bc.edu
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
        printf("\n%c\n",c);
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
        printf("\t%d",dot);
    }
    return (dot ? SUCCESS : ERROR);
}

// Checks if the string is an integer starting with '-'/'+' and containing all numerals.
int is_integer(char* input){
     // c refers to the first character in the string "input".
    char c = *input;
    printf("\n%c\n",c);
    // Checks if first char is either a digit or '+'/'-'.
    if (!(is_digit(c) || (c == '+') || (c == '-')))
        return ERROR;

    for(int i = 1; input[i] !=0; i++) {
        // If not a digit, return ERROR.
        c = input[i];
        printf("\n%c\n",c);
        if (!is_digit(c))
            return ERROR;
    }
    return SUCCESS;
}

int main(int argc, char *argv[]) {
    char* f = "+25.4.3";
    char* i = "-12.49";
    //char* fp = f.c_str();
    //char* ip = i.c_str();
    char digit = 'a';
    if (!is_floating_point_number(f))
        printf("\nSUCCESS\n");
}