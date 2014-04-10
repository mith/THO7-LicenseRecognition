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
	thresholdVal = 0.25;
	targetHigh = .65;
	targetLow = -0.650;
}


OCRImageData::~OCRImageData() {
}

unsigned int OCRImageData::getNumberInput() 
{
	return 18;
}

unsigned OCRImageData::getImageList() {
	imageList.clear();

	std::vector<std::string> tempList;
	int count = GetFileList("../../Images/*.jpg", tempList);

	// Using Index Based Accessing
	for(int i = 0; i < tempList.size(); i++) {
		imageList.push_back(ImageGray(("../../Images/" + tempList[i]).c_str()));
		imageData.push_back(getCharIndex(tempList[i][0]));
	}

	return imageList.size();
}

unsigned OCRImageData::getNextInputs(std::vector<double> &inputVals, unsigned currentImage) {
	inputVals.clear();

	if(currentImage <= imageList.size()){ 
		//inputVals.push_back(patterns.checkPixelsPerLineHorizontal(imageList[currentImage], 20));
		inputVals.push_back(patterns.checkPixelsPerLineHorizontal(imageList[currentImage], 30));
		//inputVals.push_back(patterns.checkPixelsPerLineHorizontal(imageList[currentImage], 40));
		inputVals.push_back(patterns.checkPixelsPerLineHorizontal(imageList[currentImage], 50));
		inputVals.push_back(patterns.checkPixelsPerLineHorizontal(imageList[currentImage], 60));
		//inputVals.push_back(patterns.checkPixelsPerLineHorizontal(imageList[currentImage], 70));
		inputVals.push_back(patterns.checkPixelsPerLineHorizontal(imageList[currentImage], 80));

		//inputVals.push_back(patterns.checkPixelsPerLineVertical(imageList[currentImage], 20));
		inputVals.push_back(patterns.checkPixelsPerLineVertical(imageList[currentImage], 30));
		//inputVals.push_back(patterns.checkPixelsPerLineVertical(imageList[currentImage], 40));
		inputVals.push_back(patterns.checkPixelsPerLineVertical(imageList[currentImage], 50));
		inputVals.push_back(patterns.checkPixelsPerLineVertical(imageList[currentImage], 60));
		//inputVals.push_back(patterns.checkPixelsPerLineVertical(imageList[currentImage], 70));
		inputVals.push_back(patterns.checkPixelsPerLineVertical(imageList[currentImage], 80));

		inputVals.push_back(patterns.checkSymmetryVertical(imageList[currentImage]));
		inputVals.push_back(patterns.checkSymmetryHorizontal(imageList[currentImage]));

		//inputVals.push_back(patterns.checkBlackWhiteTransisitionHorizontal(imageList[currentImage], 20));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionHorizontal(imageList[currentImage], 30));
		//inputVals.push_back(patterns.checkBlackWhiteTransisitionHorizontal(imageList[currentImage], 40));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionHorizontal(imageList[currentImage], 50));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionHorizontal(imageList[currentImage], 60));
		//inputVals.push_back(patterns.checkBlackWhiteTransisitionHorizontal(imageList[currentImage], 70));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionHorizontal(imageList[currentImage], 80));

		//inputVals.push_back(patterns.checkBlackWhiteTransisitionVertical(imageList[currentImage], 20));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionVertical(imageList[currentImage], 30));
		//inputVals.push_back(patterns.checkBlackWhiteTransisitionVertical(imageList[currentImage], 40));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionVertical(imageList[currentImage], 50));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionVertical(imageList[currentImage], 60));
		//inputVals.push_back(patterns.checkBlackWhiteTransisitionVertical(imageList[currentImage], 70));
		inputVals.push_back(patterns.checkBlackWhiteTransisitionVertical(imageList[currentImage], 80));
	}

	return inputVals.size();
}

unsigned OCRImageData::getTargetOutputs(std::vector<double> &targetOutputVals, unsigned currentImage) {
	targetOutputVals.clear();

	//Create binairy targets
	if(currentImage >= 32) {
		targetOutputVals.push_back(targetHigh);
		currentImage -= 32;
	} else {
		targetOutputVals.push_back(targetLow);
	}

	if(currentImage >= 16) {
		targetOutputVals.push_back(targetHigh);
		currentImage -= 16;
	} else {
		targetOutputVals.push_back(targetLow);
	}

	if(currentImage >= 8) {
		targetOutputVals.push_back(targetHigh);
		currentImage -= 8;
	} else {
		targetOutputVals.push_back(targetLow);
	}

	if(currentImage >= 4) {
		targetOutputVals.push_back(targetHigh);
		currentImage -= 4;
	} else {
		targetOutputVals.push_back(targetLow);
	}

	if(currentImage >= 2) {
		targetOutputVals.push_back(targetHigh);
		currentImage -= 2;
	} else {
		targetOutputVals.push_back(targetLow);
	}

	if(currentImage >= 1) {
		targetOutputVals.push_back(targetHigh);
		currentImage -= 1;
	} else {
		targetOutputVals.push_back(targetLow);
	}

	return targetOutputVals.size();
}

std::string OCRImageData::getChar(unsigned currentImage) {
	if(currentImage == 0) {
		return "A";
	} else if(currentImage == 1) {
		return "B";
	} else if(currentImage == 2) {
		return "C";
	} else if(currentImage == 3) {
		return "D";
	} else if(currentImage == 4) {
		return "E";
	} else if(currentImage == 5) {
		return "F";
	} else if(currentImage == 6) {
		return "G";
	} else if(currentImage == 7) {
		return "H";
	} else if(currentImage == 8) {
		return "I";
	} else if(currentImage == 9) {
		return "J";
	} else if(currentImage == 10) {
		return "K";
	} else if(currentImage == 11) {
		return "L";
	} else if(currentImage == 12) {
		return "M";
	} else if(currentImage == 13) {
		return "N";
	} else if(currentImage == 14) {
		return "O";
	} else if(currentImage == 15) {
		return "P";
	} else if(currentImage == 16) {
		return "Q";
	} else if(currentImage == 17) {
		return "R";
	} else if(currentImage == 18) {
		return "S";
	} else if(currentImage == 19) {
		return "T";
	} else if(currentImage == 20) {
		return "U";
	} else if(currentImage == 21) {
		return "V";
	} else if(currentImage == 22) {
		return "W";
	} else if(currentImage == 23) {
		return "X";
	} else if(currentImage == 24) {
		return "Y";
	} else if(currentImage == 25) {
		return "Z";
	} else if(currentImage == 26) {
		return "0";
	} else if(currentImage == 27) {
		return "1";
	} else if(currentImage == 28) {
		return "2";
	} else if(currentImage == 29) {
		return "3";
	} else if(currentImage == 30) {
		return "4";
	} else if(currentImage == 31) {
		return "5";
	} else if(currentImage == 32) {
		return "6";
	} else if(currentImage == 33) {
		return "7";
	} else if(currentImage == 34) {
		return "8";
	} else if(currentImage == 35) {
		return "9";
	} else {
		return "Error!!";
	}
}

int OCRImageData::getCharIndex(char character) {
	if(character == 'A') {
		return 0;
	} else if(character == 'B') {
		return 1;
	} else if(character == 'C') {
		return 2;
	} else if(character == 'D') {
		return 3;
	} else if(character == 'E') {
		return 4;
	} else if(character == 'F') {
		return 5;
	} else if(character == 'G') {
		return 6;
	} else if(character == 'H') {
		return 7;
	} else if(character == 'I') {
		return 8;
	} else if(character == 'J') {
		return 9;
	} else if(character == 'K') {
		return 10;
	} else if(character == 'L') {
		return 11;
	} else if(character == 'M') {
		return 12;
	} else if(character == 'N') {
		return 13;
	} else if(character == 'O') {
		return 14;
	} else if(character == 'P') {
		return 15;
	} else if(character == 'Q') {
		return 16;
	} else if(character == 'R') {
		return 17;
	} else if(character == 'S') {
		return 18;
	} else if(character == 'T') {
		return 19;
	} else if(character == 'U') {
		return 20;
	} else if(character == 'V') {
		return 21;
	} else if(character == 'W') {
		return 22;
	} else if(character == 'X') {
		return 23;
	} else if(character == 'Y') {
		return 24;
	} else if(character == 'Z') {
		return 25;
	} else if(character == '0') {
		return 26;
	} else if(character == '1') {
		return 27;
	} else if(character == '2') {
		return 28;
	} else if(character == '3') {
		return 29;
	} else if(character == '4') {
		return 30;
	} else if(character == '5') {
		return 31;
	} else if(character == '6') {
		return 32;
	} else if(character == '7') {
		return 33;
	} else if(character == '8') {
		return 34;
	} else if(character == '9') {
		return 35;
	} else {
		return -1;
	}
}

std::string OCRImageData::getCharFromOutputs(std::vector<double> &outputVals) {
	std::string text = "";
	unsigned imageNumber = 0;

	if(outputVals[0] > thresholdVal) {
		imageNumber += 32;
	}

	if(outputVals[1] > thresholdVal) {
		imageNumber += 16;
	}

	if(outputVals[2] > thresholdVal) {
		imageNumber += 8;
	}

	if(outputVals[3] > thresholdVal) {
		imageNumber += 4;
	}

	if(outputVals[4] > thresholdVal) {
		imageNumber += 2;
	}

	if(outputVals[5] > thresholdVal) {
		imageNumber += 1;
	}

	text += getChar(imageNumber) + " ";

	return text;
}

void OCRImageData::showVectorVals(std::string label, std::vector<double> &v) {
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
