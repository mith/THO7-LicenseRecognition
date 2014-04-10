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
	float thresholdVal;
	float targetHigh;
	float targetLow;

	const std::string imageDir;
public:
	OCRImageData(const std::string & img_dir);
	~OCRImageData();

	// Initalize OCR
	std::vector<unsigned int> getTopology();
	unsigned loadImageList();

	// Returns the number of input values read from the file:
	unsigned getNextInputs(std::vector<float> &inputVals, unsigned currentImage);
	unsigned getTargetOutputs(std::vector<float> &targetOutputVals, unsigned currentImage);

	// Return the character that is outputed
	std::string getChar(unsigned currentImage);
	int OCRImageData::getCharIndex(char character);
	std::string getCharFromOutputs(const std::vector<float> &outputVals);
	
	// Display the values of a vector
	void showVectorVals(std::string label, const std::vector<float> &v);

	// Files in folder
	int OCRImageData::GetFileList(const char *searchkey, std::vector<std::string> &list);
};

