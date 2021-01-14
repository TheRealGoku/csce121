#include <iostream>
#include <stdexcept>
#include <string>
#include "matrix_helper.h"
// no other includes are allowed

using std::cout, std::endl;
using std::invalid_argument;
using std::to_string;
using std::size_t;
using std::ostream;

/*
dynamically allocates a new rows x cols matrix
initialize all elements to 0
*/
Matrix create_matrix(size_t rows, size_t cols) {
  int **mat = new int*[rows];
  for (size_t i = 0; i < rows; i++) {
    mat[i] = new int[cols];
    for (size_t j = 0; j < cols; j++) {
      mat[i][j] = 0;
    }
  }
  return mat;
}

// overload to create square matrices
// initialize all elements to 0
Matrix create_matrix(size_t n) {
  int **mat = new int*[n];
  for (size_t i = 0; i < n; i++) {
    mat[i] = new int[n];
    for (size_t j = 0; j < n; j++) {
      mat[i][j] = 0;
    }
  }
  return mat;
}

/*
given matrices A, B
horizontally concatenate B onto A
updates and returns A, frees B
e.g.
A = [1 2 ; 3 4]
  1 2
  3 4

B = [5 6 7 ; 8 9 10]
  5  6  7
  8  9 10
  
horzcat(A, B)
  1  2  5  6  7
  3  4  8  9 10

A
  1  2  5  6  7
  3  4  8  9 10
  
B
  []
*/
Matrix& horzcat(Matrix& A, 
                size_t& rows_A, 
                size_t& cols_A, 
                Matrix& B,
                size_t& rows_B, 
                size_t& cols_B) {
  if (rows_A != rows_B) {
    throw invalid_argument("rows dont match");
    return A;
  }
  int **c = create_matrix(rows_A, cols_A + cols_B);
  for (size_t i = 0; i < rows_A; i++) {
    for (size_t j = 0; j < cols_A; j++) {
      c[i][j] = A[i][j];
    }
    for (size_t j = cols_A; j < cols_A + cols_B; j++) {
      c[i][j] = B[i][j - cols_A];
    }
  }
  for (size_t i = 0; i < rows_A; i++) {
    delete[] A[i];
  }
  delete[] A;
  for (size_t i = 0; i < rows_B; i++) {
    delete[] B[i];
  }
  delete[] B;
  B = nullptr;
  A = c;
  cols_A = cols_A + cols_B;
  cols_B = 0;
  rows_B = 0;
  return A;
}

int main() {
  // A = [1 2 ; 3 4]
  Matrix A = create_matrix(2);
  size_t rows_A = 2;
  size_t cols_A = 2;
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;
  print_matrix(A, rows_A, cols_A);
  
  // B = [5 6 7 ; 8 9 10]
  Matrix B = create_matrix(2,3);
  size_t rows_B = 2;
  size_t cols_B = 3;
  B[0][0] = 5;
  B[0][1] = 6;
  B[0][2] = 7;
  B[1][0] = 8;
  B[1][1] = 9;
  B[1][2] = 10;
  print_matrix(B, rows_B, cols_B);

  // horzcat(A, B)
  print_matrix(horzcat(A, rows_A, cols_A, B, rows_B, cols_B), rows_A, cols_A);

  // A
  print_matrix(A, rows_A, cols_A);
  
  // B
  print_matrix(B, rows_B, cols_B);
  
  // do you hear a leak?
  
  return 0;
}