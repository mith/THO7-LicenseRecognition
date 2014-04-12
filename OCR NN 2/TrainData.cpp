#include "TrainData.h"


TrainData::TrainData(std::string img_dir)
{
	std::srand(time(0));
	auto img_files = getFilelist(img_dir + "\\*.jpg");
	for (auto & file_name : img_files) {
		images.emplace_back(file_name, ImageLib::ImageGray(img_dir + "\\" + file_name));
	}
}

TrainData::~TrainData()
{
}

std::vector<std::string> TrainData::getFilelist(const std::string & searchkey)
{
	WIN32_FIND_DATA fd;
	HANDLE h = FindFirstFile(searchkey.c_str(), &fd);

	if (h == INVALID_HANDLE_VALUE) {
		return{}; // no files found
	}

	std::vector<std::string> ret_list;

	while (1) {
		ret_list.emplace_back(fd.cFileName);

		if (FindNextFile(h, &fd) == FALSE)
			break;
	}
	return ret_list;
}

const ImageData & TrainData::operator [] (unsigned int id) const
{
	return images[id];
}


const ImageData & TrainData::getRandom() const
{
	int id = (rand() * (int)(images.size() - 1) / RAND_MAX);
	return images[id];
}

size_t TrainData::numImages() const
{
	return images.size();
}

const std::vector<unsigned int> TrainData::getTopology() {
	return{ 58, 60, 36 };
}

std::vector<double> TrainData::img_to_input(const ImageLib::ImageGray & img)
{
	std::vector<double> input{
		patterns.countBlackPixelsPerRowHorizontal(img, 10),
		patterns.countBlackPixelsPerRowHorizontal(img, 25),
		patterns.countBlackPixelsPerRowHorizontal(img, 40),
		patterns.countBlackPixelsPerRowHorizontal(img, 50),
		patterns.countBlackPixelsPerRowHorizontal(img, 60),
		patterns.countBlackPixelsPerRowHorizontal(img, 75),
		patterns.countBlackPixelsPerRowHorizontal(img, 90),

		patterns.countBlackPixelsPerLineVertical(img, 10),
		patterns.countBlackPixelsPerLineVertical(img, 25),
		patterns.countBlackPixelsPerLineVertical(img, 40),
		patterns.countBlackPixelsPerLineVertical(img, 50),
		patterns.countBlackPixelsPerLineVertical(img, 60),
		patterns.countBlackPixelsPerLineVertical(img, 75),
		patterns.countBlackPixelsPerLineVertical(img, 90),

		patterns.checkSymmetryVertical(img),
		patterns.checkSymmetryHorizontal(img),

		patterns.countBlackWhiteTransisitionHorizontal(img, 10),
		patterns.countBlackWhiteTransisitionHorizontal(img, 25),
		patterns.countBlackWhiteTransisitionHorizontal(img, 40),
		patterns.countBlackWhiteTransisitionHorizontal(img, 50),
		patterns.countBlackWhiteTransisitionHorizontal(img, 60),
		patterns.countBlackWhiteTransisitionHorizontal(img, 75),
		patterns.countBlackWhiteTransisitionHorizontal(img, 90),

		patterns.countBlackWhiteTransisitionVertical(img, 10),
		patterns.countBlackWhiteTransisitionVertical(img, 25),
		patterns.countBlackWhiteTransisitionVertical(img, 40),
		patterns.countBlackWhiteTransisitionVertical(img, 50),
		patterns.countBlackWhiteTransisitionVertical(img, 60),
		patterns.countBlackWhiteTransisitionVertical(img, 75),
		patterns.countBlackWhiteTransisitionVertical(img, 90),

		patterns.firstEdgeLocationLeft(img, 10),
		patterns.firstEdgeLocationLeft(img, 25),
		patterns.firstEdgeLocationLeft(img, 40),
		patterns.firstEdgeLocationLeft(img, 50),
		patterns.firstEdgeLocationLeft(img, 60),
		patterns.firstEdgeLocationLeft(img, 75),
		patterns.firstEdgeLocationLeft(img, 90),

		patterns.firstEdgeLocationRight(img, 10),
		patterns.firstEdgeLocationRight(img, 25),
		patterns.firstEdgeLocationRight(img, 40),
		patterns.firstEdgeLocationRight(img, 50),
		patterns.firstEdgeLocationRight(img, 60),
		patterns.firstEdgeLocationRight(img, 75),
		patterns.firstEdgeLocationRight(img, 90),

		patterns.firstEdgeLocationTop(img, 10),
		patterns.firstEdgeLocationTop(img, 25),
		patterns.firstEdgeLocationTop(img, 40),
		patterns.firstEdgeLocationTop(img, 50),
		patterns.firstEdgeLocationTop(img, 60),
		patterns.firstEdgeLocationTop(img, 75),
		patterns.firstEdgeLocationTop(img, 90),

		patterns.firstEdgeLocationBottom(img, 10),
		patterns.firstEdgeLocationBottom(img, 25),
		patterns.firstEdgeLocationBottom(img, 40),
		patterns.firstEdgeLocationBottom(img, 50),
		patterns.firstEdgeLocationBottom(img, 60),
		patterns.firstEdgeLocationBottom(img, 75),
		patterns.firstEdgeLocationBottom(img, 90)};

	return input;
}

std::vector<double> TrainData::char_to_output(char c)
{
	std::vector<double> output(36, -1.0f);

	if (c >= 47 && c < 58) {
		output[c - 48] = 1.0; // Numbers 0-9 in indices 0-9
	}
	else if (c > 64 && c < 91) {
		output[c - 55] = 1.0; // Characters A-Z in indices 10-35
	}
	else if (c > 96 && c < 123) {
		output[c - 87] = 1.0;
	}
	return output;
}