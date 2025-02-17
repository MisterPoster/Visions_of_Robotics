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
#include "matrixUtils.h"
#include "vectorUtils.h"

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

   int rows = numPoints;
   int cols = 12;

   float   u[rows];
   float   v[rows];
   float   x[rows];
   float   y[rows];
   float   z[rows];
   float  zc[rows];

   readData(inputFile, u, v, x ,y, z, zc);

   int Msize = numPoints * 3 * cols;
   float M[Msize];
   int arr_counter = 0;
   int ptr_tracker = -1;

   for(int i = 0; i < numPoints * 3; i++) 
   {
      if (i % 3 == 0) { ptr_tracker++; }

      for (int j = 0; j < cols; j++)
      {
         if (i % 3 == 0)
         {
            if (j < 4)
            {
               if (arr_counter % 4 == 0) { M [arr_counter] = x[ptr_tracker]; }
               else if (arr_counter % 4 == 3) { M [arr_counter] = 1; }
               else if (arr_counter % 4 == 2) { M [arr_counter] = z[ptr_tracker]; }
               else if (arr_counter % 4 == 1) { M [arr_counter] = y[ptr_tracker]; }
            } else { M [arr_counter] = 0; }
         }
         else if (i % 3 == 1)
         {
            if (j >= 4 && j < 8)
            {
               if (arr_counter % 4 == 0) { M [arr_counter] = x[ptr_tracker]; }
               else if (arr_counter % 4 == 3) { M [arr_counter] = 1; }
               else if (arr_counter % 4 == 2) { M [arr_counter] = z[ptr_tracker]; }
               else if (arr_counter % 4 == 1) { M [arr_counter] = y[ptr_tracker]; }
            } else { M [arr_counter] = 0; }
         }
         else if (i % 3 == 2)
         {
            if (j >= 8)
            {
               if (arr_counter % 4 == 0) { M [arr_counter] = x[ptr_tracker]; }
               else if (arr_counter % 4 == 3) { M [arr_counter] = 1; }
               else if (arr_counter % 4 == 2) { M [arr_counter] = z[ptr_tracker]; }
               else if (arr_counter % 4 == 1) { M [arr_counter] = y[ptr_tracker]; }
            } else { M [arr_counter] = 0; }
         }

         arr_counter++;
      }
   }

   // --- M Transpose Creation ---
   float Mtrans[Msize];

   matrixPrint(M, 3 * numPoints, cols);
   matrixTranspose(M, 3 * numPoints, cols, Mtrans);
   matrixPrint(Mtrans, cols, 3 * numPoints);

   // --- M_T * M = A ---
   float A[12 * 12] = {0};

   matrixProduct(Mtrans, cols, numPoints * 3, M, numPoints * 3, cols, A);
   printf ("A MATRIX\n");
   matrixPrint(A, cols, cols);
   
   // --- QR Decomposition of A ---
   float Q [cols * cols];
   float R [cols * cols];
   
   matrixQR(A, cols, cols, Q, R);
   printf ("Q MATRIX\n");
   matrixPrint(Q, cols, cols);
   printf ("R MATRIX\n");
   matrixPrint(R, cols, cols);


   // --- Q * Q_T = I ---
   float Qt [cols * cols];
   matrixTranspose (Q, cols, cols, Qt);

   float Qi [cols * cols];
   matrixProduct (Q, cols, cols, Qt, cols, cols, Qi);
   matrixPrint (Qi, cols, cols);

   // --- Making vector b ---
   int row_b = 0;
   float c [rows];
   float b [cols];
   for (int i = 0; i < numPoints; i++)
   {
      c [row_b] = (u [i] * zc [i]);
      row_b++;
      c [row_b] = (v [i] * zc [i]);
      row_b++;
      c [row_b] = (zc [i]);
      row_b++;
   }
   
   matrixTimesVector (Mtrans, cols, rows, c, rows, b);
   printf ("b = mT*c should be \n");
   vectorPrint (b, cols);
   
   // --- Making vector d = Qt * b ---
   float d [cols];
   matrixTimesVector (Qt, cols, cols, b, cols, d);

   // --- Back substitution --- 
   float p [cols];
   matrixBackSubstitution (R, cols, cols, d, p);
   printf ("Projection Matrix \n");
   matrixPrint (p, 3, 4);   

   // --- Calibration Matrix k ---
   float k [9] = {0};
   matrixInternalCameraParameters (p, 3, 4, k);
   printf ("CALIB MATRIX \n");
   matrixPrint (k, 3, 3);

   return 0;

}
