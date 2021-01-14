#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "Pixel.h"

class Image {
  Pixel** image;
  unsigned int width; // columns
  unsigned int height; // rows
  std::string filename;
  
public:
  Image();
  
  ~Image();
  Image(const Image &copy);
  
  Image& operator=(Image copy) {
	width = copy.width;
	height = copy.height;
	filename = copy.filename;
	allocateImage(width, height);
	for (unsigned int j = 0; j < height; j++) {
		for (unsigned int i = 0; i < width; i++) {
			this->image[i][j] = copy.image[i][j];
		}
	}
	return *this;
  }
  Image(std::string filename);
  Image(unsigned int width, unsigned int height);
  
  Pixel*& operator[](unsigned int column);
  const Pixel* operator[](unsigned int column) const;
  unsigned int getWidth();
  unsigned int getHeight();
  
  void makeGreyscale();
  void makeSepia();
  void addColor(Pixel p);
  
  void output(std::string filename);
  
private:
  void load(std::string filename);
  void allocateImage(unsigned int width, unsigned int height);
  void clear();
};

#endif