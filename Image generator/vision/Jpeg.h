#pragma once

#ifdef VISION_EXPORTS
#define VISIONDLL_API __declspec(dllexport) 
#else
#define VISIONDLL_API __declspec(dllimport) 
#endif

#include <stdexcept>

#include "Image.h"

namespace vis {

	class Jpeg : public Image {
	public:
		VISIONDLL_API Jpeg(const Jpeg &jpeg);
		/**
		* Constructor that will create a new buffer and load image data
		* from a file.
		*/
		VISIONDLL_API Jpeg(const char *file_name, int quality = 75, Colorspace cs = RGB);
		/**
		* Constructor that will create a 'new' buffer. This will not load image
		* data from a file.
		*/
		VISIONDLL_API Jpeg(unsigned int width, unsigned int height, const char *file_name = 0, int quality = 75, Colorspace cs = RGB);
		/**
		* This will destroy the buffer.
		*/
		VISIONDLL_API ~Jpeg();

		/**
		* Will decompress the picture that should be loaded from the file.
		* @return Returns false on failure, true otherwise.
		*/
		VISIONDLL_API bool LoadFromFile();
		/**
		* Compress the image data to a jpg file format.
		* @param  quality An int from 0-100, 0 means worst, 100 means best.
		* @return         Returns false on failure.
		*/
		VISIONDLL_API bool SaveToFile(const char *file_name = 0);
	private:
		int m_quality;
	};

}
