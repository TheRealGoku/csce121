/*
DADA function definitions
*/

#include "dada.h"
#include <cmath>

int amax(const double x[], const unsigned int len) {
	double max = -1;
	int idx = -1;
	for (unsigned int i = 0; i < len; i++) {
		if (fabs(x[i]) > max) {
			max = fabs(x[i]);
			idx = i;
		} 
		
	}
	return idx;
}

double asum(const double x[], const unsigned int len) {
	double sum = 0;
	for (unsigned int i = 0; i < len; i++) {
		if (x[i] < 0) {
			sum += -1 * x[i];
		}
		else {
			sum += x[i];
		}
	}
    return sum;
}

void axpy(const double a, const double x[], double y[], const unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
		y[i] = a * x[i] + y[i];
	}
}

void copy(const double src[], double dest[], const unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
		dest[i] = src[i];
	}
}

double dot(const double x[], const double y[], const unsigned int len) {
    int dot = 0;
	for (unsigned int i = 0; i < len; i++) {
		dot += (x[i] * y[i]);
	}
    return dot;
}

double norm2(const double x[], const unsigned int len) {
	double mag = 0;
	for (unsigned int i = 0; i < len; i++) {
		mag += pow(x[i], 2);
	}
    return sqrt(mag);
}

void scale(const double a, double x[], const unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
		x[i] = a * x[i];
	}
}

void swap(double x[], double y[], const unsigned int len) {
	int a;
    for (unsigned int i = 0; i < len; i++) {
		a = x[i];
		x[i] = y[i];
		y[i] = a;
	}
}
