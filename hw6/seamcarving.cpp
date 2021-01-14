#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;


int main() {
    string filename;
    int width = 0;
    int height = 0;
    int originalWidth = 0;
	//int originalHeight = 0;
    int targetWidth = 0;
    int targetHeight = 0;
  
    cout << "Input filename: ";
    cin >> filename;
  
    cout << "Input width and height: ";
    
	if (!(cin >> width)) {
	    cout << "Error: width is a non-integer value" << endl;
		return 1;
    }
    if (!(cin >> height)) {
	    cout << "Error: height is a non-integer value" << endl;
		return 1;
    }
	cout << "Input target width and height: ";
    if (!(cin >> targetWidth)) {
	    cout << "Error: target width is a non-integer value" << endl;
		return 1;
    }
    if (!(cin >> targetHeight)) {
	    cout << "Error: target height is a non-integer value" << endl;
		return 1;
    }
  
    if (width < 1) {
	    cout << "Error: width must be greater than 0. You entered " << width << endl; 
		return 1;
    }
    if (targetWidth < 1) {
	    cout << "Error: target width must be greater than 0. You entered " << targetWidth << endl; 
		return 1;
    }
    if (height < 1) {
	    cout << "Error: height must be greater than 0. You entered " << height << endl; 
		return 1;
    }
    if (targetHeight < 1) {
	    cout << "Error: target height must be greater than 0. You entered " << targetHeight << endl; 
		return 1;
    }
    if (targetWidth > width) {
	    cout << "Error: target width must be less than width, " << targetWidth  << " is greater than " << width << endl; 
		return 1;
    }
    if (targetHeight > height) {
	    cout << "Error: target height must be less than height, " << targetHeight  << " is greater than " << height << endl; 
	    return 1;
    }
  
	// save originalWidth since width will change with carving
	originalWidth = width; 
	// save originalHeight since height will change with carving
	//originalHeight = height;  
	Pixel** image = createImage(width, height);
	if (image != nullptr) { // new returns nullptr if it fails to allocate array

		if (loadImage(filename, image, width, height)) {
		  
			// uncomment for part 2
			
			while ((width - targetWidth > 0) || (height - targetHeight > 0)) {
				if (width - targetWidth > 0) {
				    int* verticalSeam = findMinVerticalSeam(image, width, height);
				    removeVerticalSeam(image, width, height, verticalSeam);
				    deleteSeam(verticalSeam);
				    width--;
				}
				
				// this is for the extra credit
				if (height - targetHeight > 0) {
				  int* horizontalSeam = findMinHorizontalSeam(image, width, height);
				  removeHorizontalSeam(image, width, height, horizontalSeam);
				  deleteSeam(horizontalSeam);
				  height--;
				}
			}
			
		  
		    stringstream ss;
		    ss << "carved" << width << "X" << height << "." << filename;
		    outputImage(ss.str().c_str(), image, width, height);
		}
	}
	  
	// call last to remove the memory from the heap
	deleteImage(image, originalWidth);
}