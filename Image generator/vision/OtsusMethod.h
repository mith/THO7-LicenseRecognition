#pragma once

#ifdef VISION_EXPORTS
#define VISIONDLL_API __declspec(dllexport) 
#else
#define VISIONDLL_API __declspec(dllimport) 
#endif

#include "Algorithm.h"

#include <iostream>

#include <cmath>	// For sqrt() and pow().

namespace vis {

	/**
	 * Apply the Otsus method algorithm to an image. In short this algorithm will calculate a
	 * threshold value for the image.
	 * This class is an implementation of the Algorithm class.
	 */
	class OtsusMethod : public Algorithm {
	public:
		/**
		 * Construct the algorithm. Does not need parameters as this algorithm isn't dependent on any variables.
		 */
		VISIONDLL_API OtsusMethod();
		/**
		 * Apply the algorithm to the image.
		 * @param  image_src The source image
		 * @param  image_dst The resulting image.
		 */
		VISIONDLL_API void ExecuteAlgorithm(Image *image_src, Image *image_dst);
	};

}
