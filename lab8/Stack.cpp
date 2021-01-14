#include <iostream>
#include <cmath>
#include "Stack.h"
using std::cout;
using std::endl;

void push(Stack& s, double element)  {
	if (s.capacity > s.length) {
		s.A[s.length] = element;
		s.length++;
	}
	else {
		Stack x;
		x.A = new double[s.capacity * 2];
		x.capacity = s.capacity * 2;
		for (int i = 0; i < s.length; i++) {
			x.A[i] = s.A[i];
			x.length++;
		}
		x.A[x.length] = element;
		x.length++;
		Stack *y = &s;
		s = x;
	}
}

double pop(Stack& s) {
	if (s.length != 0) {
		s.length--;
		return s.A[s.length];
	}
	return NAN;
}