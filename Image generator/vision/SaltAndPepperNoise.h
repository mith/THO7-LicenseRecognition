#pragma once

#ifdef VISION_EXPORTS
#define VISIONDLL_API __declspec(dllexport) 
#else
#define VISIONDLL_API __declspec(dllimport) 
#endif

#include "Algorithm.h"
#include <iostream>

#include <ctime>	// For time() to seed the random number generator.

namespace vis {

	/**
	 * Extended class of the base class Algorithm.
	 * This algorithm will add a specified amount of noise to the image.
	 * The noise is salt and pepper, meaning white and black pixels spread
	 * over the image.
	 */
	class SaltAndPepperNoise : public Algorithm {
	public:
		/**
		 * Construct the algorithm with a ratio. The ratio is the probability that
		 * noise will occur on that pixel.
		 * @param  ratio The probability ratio.
		 */
		VISIONDLL_API SaltAndPepperNoise(unsigned int ratio);

		/**
		 * Execute the noise algorithm.
		 * @param image_src The image the noise will be applied to.
		 * @param image_dst The resulting image.
		 */
		VISIONDLL_API void ExecuteAlgorithm(Image *image_src, Image *image_dst);
	private:
		int pProbability;
	};

}
