#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

void vectorPrint(float* u , int rows)
{
  printf ("\n");
  for(int i=0;i<rows;i++){
    printf( "%7.1f \n",u[i]);
  }
  printf("\n");

}

void vectorScale(float* u, int rows, float alpha , float* v)
{
  for(int i=0; i<rows; i++){
    v[i]=alpha*u[i];
  }
}

float vectorNorm (float* u, int r)
{
  float sum = 0.0f;
  //int size = (sizeof (u)) / sizeof (u[0]);

  for (int c = 0; c < r; c++)
    sum += pow (u[c], 2);


  printf ("\n");
  return sqrt (sum);
}

void vectorAdd (float* res, float* a, float* b, int r)
{
  for (int c = 0; c < r; c++)
  {
    res[c] = a[c] + b[c];
    printf ("%f   ", res[c]);
  }

  vectorPrint (res, r);
}

void vectorSub (float* res, float* a, float* b, int r)
{
  for (int c = 0; c < r; c++)
  {
    res[c] = a[c] - b[c];
    printf ("%f   ", res[c]);
  }
  
  vectorPrint (res, r);
}

float dotProduct (float* a, float* b, int r)
{
  float dot = 0.0f;
  //int size = (sizeof (a)) / (sizeof (a[0]));
  
  for (int c = 0; c < r; c++)
    dot += (a[c] * b[c]);

  return dot;
}

