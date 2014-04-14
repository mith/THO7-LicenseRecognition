#include "Image.h"

/*
Empty constructor
*/
Image::Image() {
	image = new CImage();
	width = 0;
	height = 0;
	bpp = 0;
	pixel = nullptr;
}

/*
Create an empty image
*/
Image::Image(std::string fileName, int width, int height) : width(width), height(height), fileName(fileName) {
	image = new CImage();
	image->Create(width, height, 24);
	bpp = 24;
	pixel = new unsigned int[height * width];
	for(int i = 0; i < (width * height); i++) {
		pixel[i] = 0;
	}
}

/*
Constructor with path to image file
*/
Image::Image(std::string inputName) {
	image = new CImage();
	fileName = inputName;
	image->Load(_T((inputLocation + fileName).c_str()));
	LoadFromCImage();
}

/*
Copy constructor
*/
Image::Image(Image &img) {
	width = img.width;
	height = img.height;
	bpp = img.bpp;
	fileName = img.fileName;
	pixel = new unsigned int[height * width];
	for(int i = 0; i < (width * height); i++) {
		pixel[i] = img.pixel[i];
	}
	image = new CImage();
	image->Create(width, height, bpp);
}

/*
Destructor
*/
Image::~Image() {
	delete image;
	delete[] pixel;
}





/*
Public functions
*/

/*
Copy an image
*/
void Image::CopyImage(Image &img) {
	width = img.width;
	height = img.height;
	bpp = img.bpp;
	fileName = img.fileName;
	delete[] pixel;
	pixel = new unsigned int[height * width];
	for(int i = 0; i < (width * height); i++) {
		pixel[i] = img.pixel[i];
	}
	delete image;
	image = new CImage();
	image->Create(width, height, bpp);
}

/*
Load a file
*/
void Image::LoadImageFromFile(std::string inputName) {
	fileName = inputName;
	image->Load(_T((inputLocation + fileName).c_str()));
	LoadFromCImage();
}

/*
Save an image to a file
*/
void Image::SaveImageToFile(std::string prefixName) {
	if(pixel != nullptr) {
		int R = 0, G = 0, B = 0, A = 0, currentPixel;

		//Pitch (negative = Bottom-up DIB / positive = Bottom-down DIB)
		//locating pointer to start of image data
		int pitch = image->GetPitch();
		BYTE* imgPtr = (BYTE*)image->GetBits();

		for(int y = image->GetHeight() - 1; y >= 0; y--) {
			for(int x = image->GetWidth() - 1; x >= 0; x--) {
				currentPixel = pixel[x + (y * width)];
				*(imgPtr + pitch * y + 3 * x) = (currentPixel >> bluePixelShift) & 0xFF;
				*(imgPtr + pitch * y + 3 * x + 1) = (currentPixel >> greenPixelShift) & 0xFF;
				*(imgPtr + pitch * y + 3 * x + 2) = (currentPixel >> redPixelShift) & 0xFF;
				if(bpp > 24) {
					*(imgPtr + pitch * y + 3 * x + 3) = (currentPixel & 0xFF);
				}
			}
		}

		std::cout << (outputLocation + prefixName + fileName).c_str() << std::endl;
		image->Save(_T((outputLocation + prefixName + fileName).c_str()));
	}
}

/*
Private functions
Load an image from CImage
Array pixel[x + (y * width)]
*/
void Image::LoadFromCImage() {
	height = image->GetHeight();
	width = image->GetWidth();
	bpp = image->GetBPP();
	pixel = new unsigned int[height * width];
	int R = 0, G = 0, B = 0, A = 0;

	//Pitch (negative = Bottom-up DIB / positive = Bottom-down DIB)
	//locating pointer to start of image data
	int pitch = image->GetPitch();
	BYTE* imgPtr = (BYTE*)image->GetBits();

	for(int y = image->GetHeight() - 1; y >= 0; y--) {
		for(int x = image->GetWidth() - 1; x >= 0; x--) {
			B = *(imgPtr + pitch * y + 3 * x);
			G = *(imgPtr + pitch * y + 3 * x + 1);
			R = *(imgPtr + pitch * y + 3 * x + 2);
			if(bpp > 24) {
				A = *(imgPtr + pitch * y + 3 * x + 3);
			}
			pixel[x + (y * width)] = (R << redPixelShift) | (G << greenPixelShift) | (B << bluePixelShift) | A;
		}
	}
}