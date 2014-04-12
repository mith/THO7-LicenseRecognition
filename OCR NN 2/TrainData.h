#pragma once
#include <string>
#include <ctime>
#include <vector>
#include <windows.h>
#include <ImageLib.h>
#include "CheckPatterns.h"

struct ImageData
{
	std::string filename;
	ImageLib::ImageGray image;

	ImageData(std::string fln, ImageLib::ImageGray img)
		: filename(fln), image(img) {

	}

	char getChar() const {
		char c = filename.front();
		return (c > 96 && c < 123) ? c - 32 : c;
	}
};

class TrainData
{
private:
	std::vector<ImageData> images;
	CheckPatterns patterns;
public:
	TrainData(std::string img_dir);
	const ImageData & operator [] (unsigned int id) const;
	const ImageData & getRandom() const;
	const std::vector<unsigned int> getTopology();
	size_t numImages() const;
	std::vector<std::string> getFilelist(const std::string & searchkey);
	std::vector<double> img_to_input(const ImageLib::ImageGray & img);
	std::vector<double> char_to_output(char c);
	~TrainData();
};

