#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctime>
#include <string>
#include <sstream>
#include "readParams.h"
#include "readData.h"

using namespace std;

int main()
{
   int numPoints = 0;
   string inputFile;

   cout << "Enter the name of the calibration file: ";
        getline(std::cin, inputFile); // Read a line

   numPoints = readParams(inputFile);

   printf( "Number of Points %d \n",numPoints);

   if(numPoints<12)
   {
      printf("Not enough points. Min of 12 are needed \n"); 
      exit(0);
   }

   int cols = 12;

   float   u[numPoints];
   float   v[numPoints];
   float   x[numPoints];
   float   y[numPoints];
   float   z[numPoints];
   float  zc[numPoints];

   readData(inputFile, u, v, x ,y, z, zc);

   int Msize = numPoints * 3 * cols;
   float M[Msize];
   int arr_counter = 0;
   int ptr_tracker = 0;

   for (int i = 0; i < (numPoints * 3); i++)
   {
      if (i % 3 == 0) { ptr_tracker++; }

      for (int j = 0; j < cols; j++)
      {
         if (i % 3 == 0)
         {
	    if (j < 4)
            {
               if (arr_counter % 4 == 0) { M [arr_counter] = x[ptr_track]; }
               else if (arr_counter % 4 == 3) { M [arr_counter] = 1; }
               else if (arr_counter % 4 == 2) { M [arr_counter] = z[ptr_track]; }
               else if (arr_counter % 4 == 1) { M [arr_counter] = y[ptr_track]; }
            } else { M [arr_counter] = 0; }
         }
         else if (i % 3 == 1)
         {
	    if (j >= 4 && j < 8)
            {
               if (arr_counter % 4 == 0) { M [arr_counter] = x[ptr_track]; }
               else if (arr_counter % 4 == 3) { M [arr_counter] = 1; }
               else if (arr_counter % 4 == 2) { M [arr_counter] = z[ptr_track]; }
               else if (arr_counter % 4 == 1) { M [arr_counter] = y[ptr_track]; }
            } else { M [arr_counter] = 0; }
         }
         else if (i % 3 == 2)
         {
	    if (j >= 8)
            {
               if (arr_counter % 4 == 0) { M [arr_counter] = x[ptr_track]; }
               else if (arr_counter % 4 == 3) { M [arr_counter] = 1; }
               else if (arr_counter % 4 == 2) { M [arr_counter] = z[ptr_track]; }
               else if (arr_counter % 4 == 1) { M [arr_counter] = y[ptr_track]; }
            } else { M [arr_counter] = 0; }
         }

         arr_counter++;
      }
   }

   Mtrans [Msize];

   matrixTranspose (M, cols, (3 * numPoints), Mtrans);
 
   return 0;
}
