// matrix_vertcat.cpp
#include <iostream>
#include <stdexcept>
#include "./matrix.h"

using std::cout, std::endl;
using std::invalid_argument;
using std::size_t;

// vertically concatenate B to A (A on top of B)
// throws an invalid_argument exception on mismatched dimensions
// side effects:
//   A is reallocated to be bigger
Matrix& vertcat(Matrix& A, Matrix const& B) {
  if (A.cols != B.cols) {
	  throw invalid_argument("columns dont match");
	  return A;
  }
  
  int **c = new int*[A.rows + B.rows];
    
  for (size_t i = 0; i < A.rows; i++) {
	  c[i] = new int[A.cols];
	  for (size_t j = 0; j < A.cols; j++) {
		  c[i][j] = A.data[i][j];
	  }
  }
  for (size_t i = 0; i < B.rows; i++) {
	  c[i + A.rows] = new int[B.cols];
	  for (size_t j = 0; j < B.cols; j++) {
		  c[i + A.rows][j] = B.data[i][j];
	  }
  }

  
	for (size_t i = 0; i < A.rows; i++) {
		delete[] A.data[i];
	}
	A.rows = A.rows + B.rows;
	A.data = c;
  
  return A;
}

Matrix::~Matrix() {
  for (size_t i = 0; i < rows; i++) {
	  delete[] data[i];
  }
  delete[] data;
  data = nullptr;
}