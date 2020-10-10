#ifndef MATMUL_H
#define MATMUL_H

//Thread block size
#define MATRIX_SIZE 1024

// Matrix dimensions
// (chose as multiples of the thread block size for simplicity)
#define WM MATRIX_SIZE // Matrix M width
#define HM MATRIX_SIZE // Matrix M height
#define WN MATRIX_SIZE // Matrix N width
#define HN WM // Matrix N height
#define WP WN // Matrix P width
#define HP HM // Matrix P height


// Matrix Structure declaration
typedef struct{
	//width of matrix represented
	unsigned int width;
	//height of matrix represented
	unsigned int height;
	//number of elements between the beginnings of adjacent
	//rows in the memory layout (useful for representing sub matricies)
	unsigned int pitch;
	// Pointer to the first element of the matrix represented
	float *elements;
}Matrix;

#endif // MATMUL_H

