#pragma once

#ifdef VISION_EXPORTS
#define VISIONDLL_API __declspec(dllexport) 
#else
#define VISIONDLL_API __declspec(dllimport) 
#endif

#include "Image.h"
#include <stdio.h>

namespace vis {

	/**
	 * Class to execute algorithms on images.
	 */
	class Algorithm {
	public:
		/**
		 * Execute the implemented algorithm, using a source and destination
		 * @param image_src The source image the algorithm will work on.
		 * @param image_dst The destination image the result will be put in.
		 */
		virtual VISIONDLL_API void ExecuteAlgorithm(Image *image_src, Image *image_dst) = 0;
	};

}
