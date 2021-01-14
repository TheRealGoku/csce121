#include <cstdlib>
#include <cmath>
#include "pi.h"

using std::sqrt;

double approx_pi(unsigned seed, unsigned n) {
    // seed the random number generator
    srand(seed);
	double x[n];
	double y[n];
	
	for (int i = 0; i < n; i++) {
		x[i] = static_cast<double>(rand()) / RAND_MAX;
		y[i] = static_cast<double>(rand()) / RAND_MAX;
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (sqrt(pow(x[i], 2) + pow(y[i], 2)) <= 1) {
			cnt++;
		}
	}
	double area = static_cast<double>(cnt) / n;
	double pi = area * 4.0;
    // TODO(student):
    // simulate the dart-throwing process
    // estimate the area of the quadrant
    // estimate the value of pi
    // return the estimated value of pi
    return pi;
}
