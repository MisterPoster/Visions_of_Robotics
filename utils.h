#ifndef UTILS_H
#define UTILS_H


using namespace std;

void vectorPrint(float* u , int rows); 

void vectorScale(float* u, int rows, float alpha , float* v); 

float vectorNorm (float* u, int r);

//float* vectorSub (float*, float*, int r);
void vectorSub (float*, float*, float*, int r);

//float* vectorAdd (float*, float*, int r);
void vectorAdd (float*, float*, float*, int r);

float dotProduct (float*, float*, int r);

#endif

