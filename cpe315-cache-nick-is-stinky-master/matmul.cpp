#include <stdlib.h>
#include "matmul.h"
#include <stdio.h>

Matrix Allocate2ndMatrix(int height, int width, int init);

void matmul( float*, const float*, const float*, unsigned int, unsigned int, unsigned int);

////////////////////////////////////////////////////////////////////////////////
//! C = A * B
//! @param C          result matrix
//! @param A          matrix A
//! @param B          matrix B
//! @param hA         height of matrix A
//! @param wB         width of matrix B
////////////////////////////////////////////////////////////////////////////////

/* You'll need to modify this function such that matrix B is accessed
 * correctly once you change the memory layout to column-major. */
// old implementation
/*
 void matmul(float* C, const float* A, const float* B, unsigned int hA,
     unsigned int wA, unsigned int wB)
 {
   for (unsigned int i = 0; i < hA; ++i)
     for (unsigned int j = 0; j < wB; ++j) {
       double sum = 0;
       for (unsigned int k = 0; k < wA; ++k) {
         double a = A[i * wA + k];
         //double b = B[k * wB + j]; // b for row major
         double b = B[j*wB+k];	     // b for column major
         sum += a * b;
       }
       C[i * wB + j] = (float)sum;
     }
 }
*/
// loop unroll implementation
void matmul(float* C, const float* A, const float* B, unsigned int hA, unsigned int wA, unsigned int wB){
  for (unsigned int i=0; i< hA; ++i){
    for (unsigned int j=0; j < wB; ++j){
      float c11 = 0;
      float c12 = 0;
      float c21 = 0;
      float c22 = 0;
      for (unsigned int k=0; k < wA; ++k){
	/*        
	c11 += A[i*wA + k]*B[k*wB + j];
	c12 += A[wA*(i+1) + k]*B[k*wB + j];
        c21 += A[i*wA + k]*B[wB*k+(j+1)];
        c22 += A[wA*(i+1) + k]*B[wB*k+(j+1)];
        */
		
	c11 += A[i*wA + k]*B[j*wB+k];
	c12 += A[wA*(i+1)+k]*B[j*wB+k];
	c21 += A[i*wA + k]*B[(j+1)*wB + k];
	c22 += A[(i+1)*wA + k]*B[(j+1)*wB+k];
        
      }
      C[i*wB+j] = c11;
      C[(i+1)*wB+j] = c12;
      C[(i+1)*wB+j+1] = c21;
      C[i*wB+j+1] = c22;
    }
  }
}


// Allocate a matrix of dimensions height*width

Matrix Allocate2ndMatrix(int height, int width)
{
  Matrix M;
  M.width = M.pitch = width;
  M.height = height;
  int size = M.width * M.height;
  M.elements = NULL;

  M.elements = (float*) malloc(size*sizeof(float));

  /* This is a row-major allocation and initialization.
   * You need to modify this function which is only called
   * for Matrix B such that a column-major ordering is
   * performed. */
// populate by row major
 /* 
  for(unsigned int i = 0; i < M.height * M.width; i++)
  {
     M.elements[i] = (rand() / (float)RAND_MAX);
  }
*/
 // populate by column major
   for (unsigned int i=0;i<M.height;i++){
      for (unsigned int j=0;j<M.width;j++){
         M.elements[i+j*width] = (rand() / (float)RAND_MAX);
      }
   }


  return M;
}
