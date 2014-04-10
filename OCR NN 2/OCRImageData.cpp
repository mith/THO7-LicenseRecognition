#include "OCRImageData.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

OCRImageData::OCRImageData(const std::string & img_dir) 
:imageDir(img_dir)
{
	CheckPatterns patterns;
}


OCRImageData::~OCRImageData() {
}

std::vector<unsigned int> OCRImageData::getTopology() 
{
	return{ 18, 30, 36 };
}

unsigned OCRImageData::loadImageList() {
	imageList.clear();

	std::vector<std::string> tempList;
	int count = GetFileList((imageDir + "\\*.jpg").c_str(), tempList);

	// Using Index Based Accessing
	for(int i = 0; i < tempList.size(); i++) {
		imageList.push_back(ImageGray((imageDir + "\\" + tempList[i]).c_str()));
		unsigned char character = tempList[i][0];
		if (character > 96) {
			character -= 32;
		}
		imageData.push_back(character);
	}

	return imageList.size();
}

unsigned OCRImageData::getNextInputs(std::vector<float> &inputVals, unsigned currentImage) {
	inputVals.clear();
	if(currentImage <= imageList.size()){ 
		inputVals.push_back(patterns.checkPixelsPerLineHorizontal(imageList[currentImage], 30));
		inputVals.push_back(patterns.checkPixelsPerLineHorizontal(imageList[currentImage], 50));
		inputVals.push_back(patterns.checkPixelsPerLineHorizontal(imageList[currentImage], 60));
		inputVals.push_back(patterns.checkPixelsPerLineHorizontal(imageList[currentImage], 80));

		inputVals.push_back(patterns.checkPixelsPerLineVertical(imageList[currentImage], 30));
		inputVals.push_back(patterns.checkPixelsPerLineVertical(imageList[currentImage], 50));
		inputVals.push_back(patterns.checkPixelsPerLineVertical(imageList[currentImage], 60));
		inputVals.push_back(patterns.checkPixelsPerLineVertical(imageList[currentImage], 80));

		inputVals.push_back(patterns.checkSymmetryVertical(imageList[currentImage]));
		inputVals.push_back(patterns.checkSymmetryHorizontal(imageList[currentImage]));

		inputVals.push_back(patterns.checkBlackWhiteTransisitionHorizontal(imageList[currentImage], 30));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionHorizontal(imageList[currentImage], 50));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionHorizontal(imageList[currentImage], 60));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionHorizontal(imageList[currentImage], 80));

		inputVals.push_back(patterns.checkBlackWhiteTransisitionVertical(imageList[currentImage], 30));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionVertical(imageList[currentImage], 50));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionVertical(imageList[currentImage], 60));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionVertical(imageList[currentImage], 80));
	}

	return inputVals.size();
}

unsigned OCRImageData::getTargetOutputs(std::vector<float> &targetOutputVals, unsigned currentImage) {
	targetOutputVals.clear();
	for (unsigned int i = 0; i < 36; i++) {
		targetOutputVals.push_back(-1.0);
	}
	if (imageData[currentImage] > 47 && imageData[currentImage] < 58) {
		targetOutputVals[imageData[currentImage] - 48] = 1.0; // Numbers 0-9 in indices 0-9
	}
	else if (imageData[currentImage] > 64 && imageData[currentImage] < 91) {
		targetOutputVals[imageData[currentImage] - 55] = 1.0; // Characters A-Z in indices 10-35
	}
	return targetOutputVals.size();
}

std::string OCRImageData::getCharFromOutputs(const std::vector<float> &outputVals) {
	std::string text = " ";
	unsigned int highest = 0;
	for (unsigned int i = 1; i < outputVals.size() - 1; ++i) {
		if (outputVals[i] > outputVals[highest]) {
			highest = i;
		}
	}
	if (highest < 10) {
		text[0] = highest + 48;
	}
	else {
		text[0] = highest + 55;
	}
	return text;
}

void OCRImageData::showVectorVals(std::string label, const std::vector<float> &v) {
	std::cout << label << " ";
	for(unsigned i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " / ";
	}

	std::cout << std::endl;
}

// Files in folder

// searchkey = "c:\\kathir\\*.txt";
int OCRImageData::GetFileList(const char *searchkey, std::vector<std::string> &list) {
	WIN32_FIND_DATA fd;
	HANDLE h = FindFirstFile(searchkey, &fd);

	if(h == INVALID_HANDLE_VALUE) {
		return 0; // no files found
	}

	while(1) {
		list.push_back(fd.cFileName);

		if(FindNextFile(h, &fd) == FALSE)
			break;
	}
	return list.size();
}
