// DO NOT CHANGE ANYTHING IN THIS FILE
//   if you do, it could break the test cases
//   it will be your fault
//   you will lose points
// DO NOT CHANGE ANYTHING IN THIS FILE
#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>
#include <iomanip>
// no other includes are allowed

// typedef magic so that "Matrix" means "int**";
// if this confuses you, you can use "int**"" instead of "Matrix"
typedef int Value;
typedef Value* Row;
typedef Row* Matrix;
typedef const Value constValue;
typedef constValue* constRow;
typedef constRow const* constMatrix;


// length of n in characters
std::size_t get_width(int n) {
	if (n < 0) {
		return 1 + get_width(-n);
	}
	if (n < 10) {
		return 1;
	}
	return 1 + get_width(n/10);
}

// pretty print a matrix with right-aligned columns
void print_matrix(constMatrix matrix, std::size_t rows, std::size_t cols, std::ostream& os=std::cout) {
    // handle the empty matrix
    if (rows == 0 || cols == 0) {
        os << std::endl << "[]" << std::endl;
        return;
    }
    
    // compute column widths
	std::size_t* width = new std::size_t[cols]{0};
    for (std::size_t col = 0; col < cols; ++col) {
        for (std::size_t row = 0; row < rows; ++row) {
            std::size_t digits = get_width(matrix[row][col]);
            if (digits > width[col]) {
                width[col] = digits;
            }
        }
    }
    
    // pretty print with right-aligned columns
    os << std::endl;
    for (std::size_t row = 0; row < rows; ++row) {
        os << "|";
        for (std::size_t col = 0; col < cols; ++col) {
            os << " " << std::setw(width[col]) << matrix[row][col];
        }
        os << " |" << std::endl;
    }
    
    delete[] width;
}

#endif