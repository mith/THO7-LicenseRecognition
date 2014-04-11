#include "ImageList.h"
#include <ctime>
#include <windows.h>


ImageList::ImageList(const std::string & image_dir) : image_dir(image_dir)
{
	std::srand(std::time(0));

	auto img_files = getFilelist(image_dir + "\\*.jpg");

	for (auto & file_name : img_files) {
		char c = file_name.front();
		images.emplace_back((c > 96 && c < 123) ? c - 32 : c, ImageGray(image_dir + "\\" + file_name));
	}
}


ImageList::~ImageList()
{
}

std::vector<std::string> ImageList::getFilelist(const std::string & searchkey)
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

std::pair<char, const ImageGray &> ImageList::operator [] (int id) const
{
	return{ images[id].first, images[id].second };
}

std::pair<char, const ImageGray &> ImageList::getRandom() const
{
	int id = (rand() * (int)(images.size() - 1) / RAND_MAX);
	return{ images[id].first, images[id].second };
}