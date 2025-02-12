#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctime>
#include <string>
#include <sstream>
#include "vectorUtils.h"
#include "matrixUtils.h"

using namespace std;

void matrixPrint(float* matrix, int rows, int cols) {
    printf("number of rows and cols,%d %d \n", rows, cols);
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            printf("%6.1f ",matrix[row*cols + col]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrixProduct(float* a, int rows_a, int cols_a, float* b, int rows_b, int cols_b, float* c){
 int index = 0;
 int rows  = rows_a;
 int cols  = cols_b;

 if(cols_a == rows_b){
 for(int row = 0; row < rows; row++){
   for(int col = 0; col < cols; col++){
       index = row*cols + col;
       c[index] = 0.0; 
       for(int k = 0; k < cols_a; k++){
         c[index]=c[index]+a[row*cols_a + k]*b[col+k*cols_b];
       }
   }

 }

 }else{
	 printf("Can't multiply. Dimensions incorrect \n");
	 exit(0);
 }

}

void matrixTranspose(float* a, int rows, int cols, float* aTranspose){
 for( int row = 0; row < rows; row++){
		for( int col = 0;col < cols;col++){

		    aTranspose[col*rows+row] = a[row*cols+col];
		}
		 
 }
}

void matrixExtractCol(float*a, int rows, int cols, int col, float* column){
    int index;
    for(int row=0;row<rows;row++){
	index = col + row*cols;
        column[row] = a[index];
    }
}



void matrixQRDecomposision(float* a, int rows, int cols, float* Q, float* R) {
    // A & Q & R should be square matrices (rows x rows)
    // R is going to be upper triangular
    // Q is going to be orthogonal
        // Q's columns will also be orthonormal vectors

    // First, we need to make sure the matrix's are square
    if(rows != cols) {
        printf("Matrix is not square. Can't perform QR decomposition\n");
        return;
    }

    // Now, we need to get the q vectors by normalizing the columns of a

    for(int i = 0; i < cols; i++) {
        // Looking at the ith column of a
        float a_i_perpendicular[rows];

        // Start off a_i_perpendicular as a_i
        matrixExtractCol(a, rows, cols, i, a_i_perpendicular);

        // Calculating a_i_perpendicular (part of q_i vector)
        // Filling parts of R in the ith column while we're at it
        for(int j = 0; j < i; j++) {
            // Extracting the ith column of a
            float a_i[rows];
            matrixExtractCol(a, rows, cols, i, a_i);

            // Extracting the jth column of Q
            float q_j[rows];
            matrixExtractCol(Q, rows, cols, j, q_j);

            // Getting distance of a_i projected onto q_j
            float dotProduct = vectorDotProduct(a_i, q_j, rows);

            // Placing dotProduct into R (specifically located at r_ij)
            R[j*cols + i] = dotProduct;

            // Scaling q_j by dotProduct
            vectorScale(q_j, rows, dotProduct, q_j);

            // Subtracting the scaled q_j from a_i_perpendicular to make a new a_i_perpendicular
            vectorSub(a_i_perpendicular, a_i_perpendicular, q_j, rows);
        }

        // Now we have a complete a_i_perpendicular vector

        // Filling edge values of R in the ith column
        for(int j = 0; j < rows; j++) {
            // Looking at the jth row of the ith column of a
            if(j == i) {
                // Fill with the magnitude of a_i_perpendicular
                R[j*cols + i] = vectorMag(a_i_perpendicular, rows);
            }
        }

        // Now we fill the ith row of Q with the normalized a_i_perpendicular values
        vectorNorm(a_i_perpendicular, rows);
        for(int j = 0; j < rows; j++) {
            Q[j*cols + i] = a_i_perpendicular[j];
        }
    }

    // Now, we need to get the r values by getting the perpendicualr components of a onto the q vectors
        // q_i = a_i - a projected onto q_i direction - a projected onto q_i+1 direction - ..., all divided by the magnitude of all above
}
