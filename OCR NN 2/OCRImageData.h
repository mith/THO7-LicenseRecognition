// Neural network test control class 
// by Kevin Bosman

#pragma once
#include "ImageLib.h"
#include "CheckPatterns.h"

class OCRImageData {
private:
	std::vector<ImageGray> imageList;
	std::vector<unsigned> imageData;
	CheckPatterns patterns;
	double thresholdVal;
	double targetHigh;
	double targetLow;

	std::string imageDir;
public:
	OCRImageData(const std::string & img_dir);
	~OCRImageData();

	// Initalize OCR
	unsigned int getNumberInput();
	unsigned getImageList();

	// Returns the number of input values read from the file:
	unsigned getNextInputs(std::vector<double> &inputVals, unsigned currentImage);
	unsigned getTargetOutputs(std::vector<double> &targetOutputVals, unsigned currentImage);

	// Return the character that is outputed
	std::string getChar(unsigned currentImage);
	int OCRImageData::getCharIndex(char character);
	std::string getCharFromOutputs(std::vector<double> &outputVals);
	
	// Display the values of a vector
	void showVectorVals(std::string label, std::vector<double> &v);

	// Files in folder
	int OCRImageData::GetFileList(const char *searchkey, std::vector<std::string> &list);
};

