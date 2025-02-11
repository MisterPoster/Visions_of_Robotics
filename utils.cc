// Homework 1, Robotics 444
// By: Andrew Gallimore

#include <stdio.h>
#include <cmath>
#include "utils.h"

using namespace std;

void vectorPrint(float* u , int rows) {
  printf ("\n");
  for(int i=0;i<rows;i++) {
    printf( "%7.1f \n",u[i]);
  }
  printf("\n");
}

void vectorScale(float* u, int rows, float scalar, float* result) {
  for(int i=0; i<rows; i++) {
    result[i]=scalar*u[i];
  }
}

void vectorNorm(float* a, int rows) {
  // Getting magnitude of vector
  float mag = 0.0;
  for (int c = 0; c < rows; c++) {
    mag += pow(a[c], 2);
  }
  mag = sqrt(mag);

  // Dividing each element by the magnitude
  for(int i=0; i<rows; i++) {
    a[i] = a[i] / mag;
  }
}

void vectorAdd(float* result, float* a, float* b, int rows) {
  // Adding each element in the vectors
  for (int c = 0; c < rows; c++) {
    result[c] = a[c] + b[c];
  }
}

void vectorSub(float* result, float* a, float* b, int rows) {
  // Subtracting each element in the vectors
  for (int c = 0; c < rows; c++) {
    result[c] = a[c] - b[c];
  }
}

float vectorDotProduct(float* a, float* b, int rows) {
  float dot = 0.0;

  // Caclulating the dot product by multiplying each element in the vectors, then suming
  for (int c = 0; c < rows; c++) {
    dot += (a[c] * b[c]);
  }

  // And returning it
  return dot;
}

