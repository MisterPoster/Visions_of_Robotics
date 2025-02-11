// Homework 1, Robotics 444
// By: Andrew Gallimore

#include "utils.h"
#include <stdio.h>

using namespace std;

int main () 
{
    float a[] = { 1, 2, 3 };
    float b[] = { 9, 1, 4 };
    float c[] = {-7, 3, 4 };

    int rows = 3;
    float scalar = 2.0;
    
    // Print initial values
    printf("Printing vector a:\n");
    vectorPrint(a, rows);
    printf("Printing vector b:\n");
    vectorPrint(b, rows);
    printf("Printing vector c:\n");
    vectorPrint(c, rows);

    // Testing scaling
    float d[] = { 0, 0, 0 };
    printf ("Printing the vector a scaled by 2:\n");
    vectorScale(a, rows, scalar, d);
    vectorPrint(d, rows);

    // Testing normalization
    printf("Printing vector a normalized:\n");
    vectorNorm(a, rows);
    vectorPrint(a, rows);
    printf("\n");

    // Testing addition
    float e[] = {0,0,0};
    printf("Printing vector b and c added:\n");
    vectorAdd(e, b, c, rows);
    vectorPrint(e, rows);

    // Testing subtraction
    float f[] = {0,0,0};
    printf("Printing vector b and c subtracted:\n");
    vectorSub(f, b, c, rows); 
    vectorPrint(f, rows);

    // Testing dot product
    printf("Printing the dot of b on c:\n\n");
    printf("  %.2f\n", vectorDotProduct(b, c, rows));
    printf("\n");

}
