#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

int main() {
	string y = "test.ppm";
	Pixel** image1 = createImage(3, 4);
	if (loadImage(y, image1, 3, 4)) {
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 4; c++) {
				cout << energy(image1, r, c, 3, 4) << " ";
			}
			cout << endl;
		}
	}
	return 0;
}