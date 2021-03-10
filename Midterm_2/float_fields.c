/*
 * Program to print components of a floar
 *
 * Author: Ilan Valencius - valencig@bc.edu
 */

//Packages
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Typedef for a converter union type.
typedef union converter {
    float f;
    unsigned int u;
} converter;

// Function to convert frim binary to decimal.
unsigned int bin_to_dec(char * input) {
    unsigned int value = 0u;
    while (*input) {
        value *= 2;
        value += *input - '0';
        ++input;
    }
    return value;
}

// Print out the binary representation of input and saves is as unsigned int in union type.
void print_binary(unsigned int num) {
    unsigned int shift = 31;
    unsigned int mask = 1 << shift;
    printf("\nBinary representation:\n");
    while(mask) {
        if(num & mask)
            printf("1");
        else
            printf("0");
        mask >>= 1;
    }
}

// Prints out the proper sign in decimal and binary.
void print_sign(unsigned int num) {
    unsigned int shift = 31;
    unsigned int mask = 1 << shift;
    unsigned int sign = mask & num;
    sign >>=31;
    printf("\n\nSign: ");
    printf("\n\tbinary: %d",sign);
    printf("\n\tdecimal: %d",sign);
}

// Prints out the proper exponent.
void print_exponent(unsigned int num) {
    unsigned int shift = 30;
    unsigned int mask = 1 << shift;
    printf("\n\nExponent:");
    printf("\n\tbinary: ");
    char binary[32] = "";
    while (shift >= 23) {
        unsigned result = mask & num;
        result = result >> shift;
        char result_char = result + '0';
        putchar(result_char);
        strncat(binary, &result_char,1);
        mask >>= 1;
        --shift;
    }
    unsigned int result_dec = bin_to_dec(binary);
    printf("\n\tdecimal: %u ",result_dec);
    printf("\n\twithout bias: %u",(result_dec-127));
}

// Prints the mantissa binary (with added 1) and in decimal
void print_mantissa(unsigned int num) {
    unsigned int mant_mask = 0x7fffff;
    unsigned int mantissa = num & mant_mask;
    unsigned int shift = 22;
    unsigned int mask = 1 << shift;
    unsigned int inverse_mask = ~mask;
    float value = 1.0;
    float weight = 1.0;
    char binary[32] = "";
    while(mantissa) {
        unsigned result = mask & mantissa;
        result = result >> shift;
        char result_char = result + '0';
        // Adjust weights and value 
        weight /= 2.0;
        value += result * weight;
        strncat(binary, &result_char,1);
        //printf("\n\t\tNew binary: %s",binary);
        mantissa = mantissa & inverse_mask;
        mask >>= 1;
        inverse_mask >>= 1;
        --shift;
    }
    
    printf("\n\nMantissa:");
    printf("\n\tbinary (with added 1): 1.%s",binary);
    printf("\n\tdecimal: %f", value);
}

/*void print_sign(input.u) {
    printf("\n\nSign:");
    printf("\n\tbinary: ");
    printf("\n\tdecimal: %d",);
}*/

/*
 * Takes input float value and calls appropriate functions.
 */
int main(void) {
    converter input;
    printf("> ");
    while( scanf("%f", &input.f)) {
        print_binary(input.u);
        print_sign(input.u);
        print_exponent(input.u);
        print_mantissa(input.u);
        // Print Carrot to start next loop
        printf("\n> ");
    }

    return EXIT_SUCCESS;
}

