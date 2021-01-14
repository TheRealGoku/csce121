#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <cmath>
#include <limits>
#include "functions.h"

using namespace std;

/***************************************************************************
 * 
 * This provided code uses C-style strings.
 * Later this semester the students will be learning and using C++ Strings 
 * instead.
 * It is important to know about C-style strings because they are used
 * in a lot of code. Unless you have a specific, compelling reason to use C-style
 * strings, once you learn C++ Strings, use std::string (defined in the <string> header) instead. 
 * std::string is easier, safer, and more flexible. 
 *
 ***************************************************************************/

/*  Function processImage
 *  choice: char representing which type of image processing to perform
 *  image: 2d-array of Pixels (structs)
 *  Return value: none
 */
 // You should not modify this function unless you add another processing option. //
void processImage(char choice, Pixel image[MAX_WIDTH][MAX_HEIGHT]) {
  const int maxFilenameSize = 100;
  char originalImageFilename[maxFilenameSize];
  char outputImageFilename[maxFilenameSize+6]; // maxFilenameSize plus 6 for adding on "sepia." ".copy" is smaller so works as well
  int width = 0, height = 0;
  
  // get filename, width and height from user
  cout << "Image filename: ";
  cin >> originalImageFilename;
  width = getInteger("width", 1, MAX_WIDTH); // ensure user does not input value greater than the MAX_WIDTH for our array
  height = getInteger("height", 1, MAX_HEIGHT); // ensure user does not input value greater than the MAX_HEIGHT for our array
  
  // load image
  if (loadImage(originalImageFilename, image, width, height)) {
    // only get in here if image loaded successfully
  
    // modify image
    switch (toupper(choice)) {
      case 'G':
        grayscaleImage(image, width, height);
        strcpy(outputImageFilename,"grey.");
        strcat(outputImageFilename, originalImageFilename);
        break;
      case 'S':
        sepiaImage(image, width, height);
        strcpy(outputImageFilename,"sepia.");
        strcat(outputImageFilename, originalImageFilename);
        break;
    }
    
    // output image
    outputImage(outputImageFilename, image, width, height);
  }
}



/*  Function loadImage
 *  filename: c-string which is the ppm file to read
 *  image: 2d-array of Pixels (structs)
 *  width: int for the width of the image array
 *  height: int for height of the image array
 *  Return value: bool true if the image loads, bool false if the image fails to load
 */
 // You should complete this function. //
bool loadImage(const char filename[], Pixel image[MAX_WIDTH][MAX_HEIGHT], int width, int height) {
  cout << "Loading image..." << endl;
  // declare/define and open input file stream
  ifstream ifs (filename);
  
  // check if input stream opened successfully
  if (!ifs.is_open()) {
    cout << "Error: failed to open input file " << filename << endl;
    return false;
  }
  
  // get type from preamble
  char type[3];
  ifs >> type; // should be P3
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
    cout << "Error: type is " << type << "instead of P3" << endl;
    return false;
  }
  
  // get width (w) and height (h) from preamble
  int w = 0, h = 0;
  ifs >> w >> h;
  if (w != width) { // check that width matches what was passed into the function
    cout << "Error: file width does not match input" << endl;
    cout << " - input width: " << width << endl;
    cout << " -  file width: " << w << endl;
    return false;
  }
  if (h != height) { // check that height matches what was passed into the function
    cout << "Error: file height does not match input" << endl;
    cout << " - input height: " << height << endl;
    cout << " -  file height: " << h << endl;
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
  // complete this part
  for (long r = 0; r < height; r++) {  
	  for (long c = 0; c < width; c++) {
		string line;
		string line1;
		string line2;
		
		if (getline(ifs, line) && getline(ifs, line1) && getline(ifs, line2)) {
			istringstream iss(line);
			istringstream iss1(line1);
			istringstream iss2(line2);
			
			iss >> image[c][r].r;
			iss1 >> image[c][r].g;
			iss2 >> image[c][r].b;
		}
		else {
			cout << "error" << endl;
		}
		  
	  }
  }
 
  return true;
}



/*  Function grayscale
 *  image: 2d-array of Pixels (structs)
 *  width: int for the width of the image array
 *  height: int for height of the image array
 *  Return value: none, but image should be modified to be grayscale colors
 */
 // You should write this function. //
void grayscaleImage(Pixel image[MAX_WIDTH][MAX_HEIGHT], int width, int height) {
  cout << "Making grayscale image... " << endl;
  for (long c = 0; c < width; c++) {
	  for (long r = 0; r < height; r++) {
		  int avg = (int)((image[r][c].r + image[r][c].g + image[r][c].b) / 3);
		  image[r][c].r = avg;
		  image[r][c].g = avg;
		  image[r][c].b = avg;
	  }
  }
  // iterate through 2d image of Pixels and convert them to grayscale
}



/*  Function sepiaImage
 *  image: 2d-array of Pixels (structs)
 *  width: int for the width of the image array
 *  height: int for height of the image array
 *  Return value: none, but image should be modified to be sepia colors
 */
 // You should write this function. //
void sepiaImage(Pixel image[MAX_WIDTH][MAX_HEIGHT], int width, int height) {
  cout << "Making sepia image... " << endl;
  for (long c = 0; c < width; c++) {
	  for (long r = 0; r < height; r++) {
		  int red = round((0.393 * image[r][c].r) + (0.769 * image[r][c].g) + (0.189 * image[r][c].b));
		  int green = round((0.349 * image[r][c].r) + (0.686 * image[r][c].g) + (0.168 * image[r][c].b));
		  int blue = round((0.272 * image[r][c].r) + (0.534 * image[r][c].g) + (0.131 * image[r][c].b));
		  if (red > 255) {red = 255;}
		  if (green > 255) {green = 255;}
		  if (blue > 255) {blue = 255;}
		  image[r][c].r = red;
		  image[r][c].g = green;
		  image[r][c].b = blue;
		  //image[r][c].r = 0;
		  //image[r][c].g = 0;
		  //image[r][c].b = 0;
	  }
  }
  // iterate through 2d image of Pixels and convert them to sepia
}



/*  Function outputImage
 *  filename: c-string which is the ppm file to write
 *  image: 2d-array of Pixels (structs)
 *  width: int for the width of the image array
 *  height: int for height of the image array
 *  Return value: none, but ppm file should be created
 */
 // You should write this function. //
void outputImage(const char filename[], const Pixel image[MAX_WIDTH][MAX_HEIGHT], int width, int height) {
  cout << "Outputting image..." << endl;
  // declare/define and open output file stream
    ofstream ofs (filename);
	if (!ofs.is_open()) {
		cout << "Error: failed to open output file " << filename << endl;
	}
	ofs << "P3\n";
	ofs << width << " " << width << endl;
	ofs << 255 << endl;
	for (long r = 0; r < height; r++) {
		string x = "";
		for (long c = 0; c < height; c++) {
			x += (to_string(image[c][r].r) + " ");
			x += (to_string(image[c][r].g) + " ");
			x += (to_string(image[c][r].b) + " ");
		}
		x += "\n";
		ofs << x;
	}
	
	

  
  // check if output stream opened successfully
  
  // output preamble
  
  // output pixels
  
}



/*  Function printMenu
 *  Return value: none
 */
 // You should not modify this function. //
void printMenu() {
  cout << "--------------------------" << endl;
  cout << " 'G': Make grayscale image" << endl;
  cout << " 'S': Make sepia image" << endl;
  cout << " 'Q': Quit" << endl;
  cout << "--------------------------" << endl;
  cout << endl << "Please enter your choice: ";
}



/*  Function getInteger
 *  label: label for outputing what the user is inputting, it should work when used as "Please enter <label>"
 *  min: int value indicating the smallest value the user should provide
 *  max: int value indicating the largest value the user should provide
 *  Return value: int value within the range min <= value <= max
 */
 // You should not modify this function. //
int getInteger(const char label[], int min, int max) {
  // get value from user repeatedly until input matches requirements
  int num = 0;
  do {
    cin.clear(); // reset stream states
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
    
    cout << "Please enter " << label << " (" << min << " - " << max << "): ";
    cin >> num;
  } while (!cin.good() || num < min || num > max); // while input does not match requirements
  return num;
}