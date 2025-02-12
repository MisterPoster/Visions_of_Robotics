#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctime>
#include <string>
#include <sstream>
#include "utils.h"

#include <iomanip>

using namespace std;

int main () 
{
    float u[] = { 1, 2, 3 };

    float v[] = { 4, 5, 6 }; // 2 4 6

    float x[] = { 9, 1, 4 };

    int rows = 3;

    float alpha = 2.0;
    
    printf ("Printing u\n");
    vectorPrint (u, rows);

    printf ("Printing the vector scaling of u\n");
    vectorScale (u, rows, alpha, v);
    vectorPrint (v, rows);

    printf ("Printing the mag of u\n");
    printf ("%.2f", vectorNorm (u, rows));
    vectorPrint (u, rows);
    printf ("\n\n");
	
    printf ("Printing the mag of v\n");
    printf ("%.2f", vectorNorm (v, rows));
    vectorPrint (v, rows);
    printf ("\n\n");

    float y [] = {0,0,0};
    printf ("Printing the sum of v and x\n");
    vectorAdd (y, v, x, rows);
    printf ("\n\n");

    float z [rows];
    printf ("Printing the difference of u and x\n");
    vectorSub (z, u, x, rows); 
    printf ("\n");

    printf ("Printing the dot between u and x\n");
    printf ("%.0f\n", dotProduct (u, x, rows));

}
