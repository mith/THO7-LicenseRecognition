/*=============================================================================

       Image shell class

	   Kevin Bosman

	   This image class uses the standard microsoft libary atlimage.h and
	   is used to provide an easy way to edit images.
	   The pixels are saves in an int array the length of width * height.
	   
	   pixels[X + Y * width];

	   Every pixel is an integer with the RGB and alpha values stores in 
	   blocks of 8 bits.

	   RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA

	   These can be read by bitshifting and then and with 0xFF to get only 
	   the 8 bits for a color.

	   Images are always saved and loaded in a relative folder in the project

	   ../Images/Origineel/ and ../Image/Nieuw/

=============================================================================*/


#ifndef Image_H
#define Image_H
#include <atlimage.h>
#include <string>
#include <iostream>

//Shift values
#define redPixelShift 24
#define greenPixelShift 16
#define bluePixelShift 8
#define alphaPixelShift 0

class Image {
private:
	CImage* image;
	std::string fileName;
	std::string inputLocation = "../Images/Origineel/";
	std::string outputLocation = "../Images/Nieuw/";

	int height;
	int width;
	int bpp;
	unsigned int *pixel;

	//Copy the contents from CImage object
	void LoadFromCImage();
public:
	//Constructors

	//Create an empty image
	Image();
	//Create an image from file
	Image(std::string fileName);
	//Create an empty image from dimensions
	Image(std::string fileName, int width, int height);
	//Copy an image
	Image(Image &img);
	//Destructor
	~Image();

	//public functions

	//Copy another image to this object
	void CopyImage(Image &img);
	//Load an image from file
	void LoadImageFromFile(std::string fileName);
	//Save image to a file
	void SaveImageToFile(std::string prefixName);

	//Return the width
	inline int GetWidth() { return width; }
	//Return the height
	inline int GetHeight() { return height;	}
	//Return the bytes per pixel
	inline int GetBPP() { return bpp; }

	//Get RGB pixel value
	inline int GetPixel(int x, int y) { return pixel[x + (y * width)]; }
	//Get red pixel value
	inline int GetPixelRed(int x, int y) { return (pixel[x + (y * width)] >> 24) & 0xFF; }
	//Get green pixel value
	inline int GetPixelGreen(int x, int y) { return (pixel[x + (y * width)] >> 16) & 0xFF; }
	//Get blue pixel value
	inline int GetPixelBlue(int x, int y) { return (pixel[x + (y * width)] >> 8) & 0xFF; }

	//Set RGB pixel value
	inline void SetPixel(int x, int y, int value) {	pixel[x + (y * width)] = value;	}
	//Set red pixel value
	inline void SetPixelRed(int x, int y, int value) { pixel[x + (y * width)] |= (value & 0xFF) << 24; }
	//Set green pixel value
	inline void SetPixelGreen(int x, int y, int value) { pixel[x + (y * width)] |= (value & 0xFF) << 16; }
	//Set blue pixel value
	inline void SetPixelBlue(int x, int y, int value) { pixel[x + (y * width)] |= (value & 0xFF) << 8; }

};

#endif