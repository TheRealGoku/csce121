#include "StackDouble.h"

StackDouble::StackDouble() {
	double* A = new double[1];
	length = 0;
	capacity = 1;
}

StackDouble::~StackDouble() {
	delete[] A;
}

void StackDouble::push(double element) {
	if (capacity > length) {
		A[length] = element;
		length++;
	}
	else {
		double* x = new double[capacity * 2];
		capacity *= 2;
		for (int i = 0; i < length; i++) {
			x[i] = A[i];
		}
		x[length] = element;
		length++;
		delete[] A;
		A = x;
	}
}

double StackDouble::pop() {
	if (length != 0) {
		length--;
		return A[length];
	}
	return NAN;
}