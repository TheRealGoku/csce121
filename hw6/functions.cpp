#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;


Pixel** createImage(int width, int height) {
    cout << "Start createImage... " << endl;
  
    // Create a one dimensional array on the heap of pointers to Pixels 
    //    that has width elements (i.e. the number of columns)
    Pixel** image = new Pixel*[width];
  
    bool fail = false;
  
    for (int i=0; i < width; ++i) { // loop through each column
        // assign that column to a one dimensional array on the heap of Pixels
        //  that has height elements (i.e. the number of rows)
        image[i] = new Pixel[height];
    
        if (image[i] == nullptr) { // failed to allocate
        fail = true;
        }
    }
  
    if (fail) { // if any allocation fails, clean up and avoid memory leak
		// deallocate any arrays created in for loop
		for (int i=0; i < width; ++i) {
		delete [] image[i]; // deleting nullptr is not a problem
		}
		delete [] image; // dlete array of pointers
		return nullptr;
    }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
    for (int row=0; row<height; ++row) {
		for (int col=0; col<width; ++col) {
		  //cout << "(" << col << ", " << row << ")" << endl;
		  image[col][row] = { 0, 0, 0 };
		}
    }
    cout << "End createImage... " << endl;
    return image;
}

void deleteImage(Pixel** image, int width) {
    cout << "Start deleteImage..." << endl;
    // avoid memory leak by deleting the array
    for (int i=0; i<width; ++i) {
		delete [] image[i]; // delete each individual array placed on the heap
    }
    delete [] image;
    image = nullptr;
}

int* createSeam(int length) {
	//int (*x)[length] = {0};
	int* x = new int[length];
	for (int i = 0; i < length; i++) {
		x[i] = 0;
	}
	return x;
}

void deleteSeam(int* seam) {
	delete[] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
	ifstream ifs (filename);
  
	if (!ifs.is_open()) {
		cout << "Error: failed to open input file - " << filename << endl;
		return false;
	}
	  
	// get type from preamble
	char type[3];
	ifs >> type; // should be P3
	if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
		cout << "Error: type is " << type << " instead of P3" << endl;
		return false;
	}
	  
	// get width (w) and height (h) from preamble
	int w = 0, h = 0;
	if (!(ifs >> w)) {
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	if (!(ifs >> h)) {
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	//ifs >> w >> h;
	if (w != width) { // check that width matches what was passed into the function
		cout << "Error: input width (";
		cout << width << ") does not match value in file (";
		cout << w << ")" << endl;
		return false;
	}
	if (h != height) { // check that height matches what was passed into the function
		cout << "Error: input height (";
		cout << height << ") does not match value in file (";
		cout << h << ")" << endl;
		return false;
	}
	  
	// get maximum value from preamble
	int colorMax = 0;
	ifs >> colorMax;
	if (colorMax != 255) {
		cout << "Error: file is not using RGB color values." << endl;
		return false;
	}

	// get RGB pixel values
	
	for (int r = 0; r < height; r++) { 	
		for (int c = 0; c < width; c++) {
			int red;
			int green;
			int blue;
			
			if (ifs >> red && ifs >> green && ifs >> blue) {
				if (red > 255 || red < 0) {
					cout << "Error: invalid color value " << red << endl;
					return false;
				}
				if (green > 255 || green < 0) {
					cout << "Error: invalid color value " << green << endl;
					return false;
				}
				if (blue > 255 || blue < 0) {
					cout << "Error: invalid color value " << blue << endl;
					return false;
				}
				image[c][r].r = red;
				image[c][r].g = green;
				image[c][r].b = blue;
			}
			else {
				if (ifs.eof()) {
					cout << "Error: not enough color values" << endl;
				}
				else {
					cout << "Error: read non-integer value" << endl;
				}
				return false;
			}
		}
	}
	string extra;
	if (ifs >> extra) {
		cout << "Error: too many color values" << endl;
		return false;
	}
	return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {
	ofstream ofs (filename);
	if (!ofs.is_open()) {
		cout << "Error: failed to open input file " << filename << endl;
		return false;
	}
	ofs << "P3\n" << width << " " << height << "\n255" << endl;
		
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			ofs << image[c][r].r << endl << image[c][r].g << endl << image[c][r].b << endl;
		}
	}
	return true;
}

int energy(Pixel** image, int y, int x, int width, int height) { 
	
	static int ow = -1, oh = -1;
	static int r;
	static int **values;
	if (!r) {
		values = new int*[width];
		for (int i = 0; i < width; i++) {
			values[i] = new int[height];
		}
		r = 1;
	}
	if (ow != width || oh != height) {
		for (int c = 0; c < width; c++) {
			for (int r = 0; r < height; r++) {
				int total = 0;
	
				Pixel p1, p2;
				p1 = image[(c + 1) % width][r];
				p2 = image[(c - 1 + width) % width][r];
				
				total += pow(p1.r - p2.r, 2) + pow(p1.g - p2.g, 2) + pow(p1.b - p2.b, 2);
				
				p1 = image[c][(r + 1) % height];
				p2 = image[c][(r - 1 + height) % height];
				
				total += pow(p1.r - p2.r, 2) + pow(p1.g - p2.g, 2) + pow(p1.b - p2.b, 2);
				values[c][r] = total;
			}
		}
		ow = width;
		oh = height;
	}
	
	return values[x][y];
}

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
	seam[0] = start_col;
	int total = energy(image, 0, start_col, width, height);
	int idx = 0;
	for (int i = 0; i < height - 1; i++) {
		int bottom = energy(image, i + 1, seam[idx], width, height);
		int left = (seam[idx] == 0) ? 390151 : energy(image, i + 1, seam[idx] - 1, width, height);
		int right = (seam[idx] == width - 1) ? 390151 : energy(image, i + 1, seam[idx] + 1, width, height);
		idx++;
		if (bottom > left && right > left) {
			total += left;
			seam[idx] = seam[idx - 1] - 1;
		}
		else if (bottom > right && right <= left) {
			total += right;
			seam[idx] = seam[idx - 1] + 1;
		}
		else {
			total += bottom;
			seam[idx] = seam[idx - 1];
		}
	
		/*if (seam[idx] == width - 1) {
			int bottom = energy(image, i + 1, seam[idx], width, height);
			int left = energy(image, i + 1, seam[idx] - 1, width, height);
			idx++;
			if (bottom > left) {
				total += left;
				seam[idx] = seam[idx - 1] - 1;
			}
			else {
				total += bottom;
				seam[idx] = seam[idx - 1];
			}
		}
		else if (seam[idx] == 0) {
			int bottom = energy(image, i + 1, seam[idx], width, height);
			int right = energy(image, i + 1, seam[idx] + 1, width, height);
			idx++;
			if (bottom > right) {
				total += right;
				seam[idx] = seam[idx - 1] + 1;
			}
			else {
				total += bottom;
				seam[idx] = seam[idx - 1];
			}
		}
		else {
			int bottom = energy(image, i + 1, seam[idx], width, height);
			int right = energy(image, i + 1, seam[idx] + 1, width, height);
			int left = energy(image, i + 1, seam[idx] - 1, width, height);
			idx++;
			if (bottom > left && right > left) {
				total += left;
				seam[idx] = seam[idx - 1] - 1;
			}
			else if (bottom > right && right <= left) {
				total += right;
				seam[idx] = seam[idx - 1] + 1;
			}
			else {
				total += bottom;
				seam[idx] = seam[idx - 1];
			}
		}*/
	}
	return total;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {

	seam[0] = start_row;
	int total = energy(image, start_row, 0,  width, height);
	int idx = 0;
	for (int i = 0; i < width - 1; i++) {
		int right = energy(image, seam[idx], i + 1, width, height);
		int top = (seam[idx] == 0) ? 390151 : energy(image, seam[idx] - 1, i + 1, width, height);
		int bottom = (seam[idx] == height - 1) ? 390151 : energy(image, seam[idx] + 1, i + 1, width, height);
		idx++;
		if (right > bottom && bottom < top) {
			total += bottom;
			seam[idx] = seam[idx - 1] + 1;
		}
		else if (right > top && bottom >= top) {
			total += top;
			seam[idx] = seam[idx - 1] - 1;
		}
		else {
			total += right;
			seam[idx] = seam[idx - 1];
		}
	}
	return total;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
	int* seam = createSeam(height);
	int col = 0;
	int min = loadVerticalSeam(image, 0, width, height, seam);
	for (int i = 1; i < width; i++) {
		int energy = loadVerticalSeam(image, i, width, height, seam);
		if (energy < min) {
			min = energy;
			col = i;
		}
	}
	loadVerticalSeam(image, col, width, height, seam);
	return seam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
	int* seam = createSeam(width);
	int row = 0;
	int min = loadHorizontalSeam(image, 0, width, height, seam);
	for (int i = 1; i < height; i++) {
		int energy = loadHorizontalSeam(image, i, width, height, seam);
		if (energy < min) {
			min = energy;
			row = i;
		}
	}
	loadHorizontalSeam(image, row, width, height, seam);
	return seam;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
	for (int r = 0; r < height; r++) {
		for (int c = verticalSeam[r]; c < width - 1; c++) {
			image[c][r] = image[c + 1][r];
		}
	}
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
	for (int c = 0; c < width; c++) {
		for (int r = horizontalSeam[c]; r < height - 1; r++) {
			image[c][r] = image[c][r + 1];
		}
	}
}

