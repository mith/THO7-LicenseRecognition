#pragma once
#include <string>
#include <memory>
#include <utility>

#include "ImageLib.h"

using namespace ImageLib;

class ImageList
{
private:
	const std::string image_dir;
	std::vector<std::pair<char, ImageGray>> images;

	std::vector<std::string> getFilelist(const std::string & searchkey);
public:
	ImageList(const std::string & image_dir);
	~ImageList();

	std::pair<char, const ImageGray &> operator [] (int id) const
	{
		return{ images[id].first, images[id].second };
	}

	std::pair<char, const ImageGray &> getRandom () const
	{
		int id = (rand() * (int)(images.size() - 1) / RAND_MAX);
		return{ images[id].first, images[id].second };
	}

	size_t numImages() const
	{
		return images.size();
	}
};

