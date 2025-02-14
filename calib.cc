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

using namespace std;

int main(){

int numPoints = 0;
string inputFile;

cout << "Enter the name of the calibration file: ";
    getline(std::cin, inputFile); // Read a line

numPoints = readParams(inputFile);

printf( "Number of Points %d \n",numPoints);

if(numPoints<12){
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

   for(int i = 0; i < numPoints * 3; i++) {

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

   float Mtrans[Msize];

   matrixPrint(M, 3 * numPoints, cols);
   matrixTranspose(M, 3 * numPoints, cols, Mtrans);
   matrixPrint(Mtrans, cols, 3 * numPoints);
   float A[12 * 12] = {0};
   matrixPrint(A, cols, cols);

   matrixProduct(Mtrans, cols, numPoints * 3, M, numPoints * 3, cols, A);

   matrixPrint(A, cols, cols);
   
   float Q[cols * cols] = {0};
   float R[cols * cols] = {0};
   
   matrixQR(A, cols, cols, Q, R);
 
   matrixPrint(Q, cols, cols);
   matrixPrint(R, cols, cols);

   float Qt [cols * cols] = {0};
   matrixTranspose (Q, cols, cols, Qt);

   float Qi [cols * cols] = {0};
   matrixProduct (Q, cols, cols, Qt, cols, cols, Qi);
   matrixPrint (Qi, cols, cols);


   



   float cam [9] = {0};
   matrixInternalCameraParameters (A, cols, cols, cam);

   // matrixPrint (cam, 3, 3);

   return 0;

}
