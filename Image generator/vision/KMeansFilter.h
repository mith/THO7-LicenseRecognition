#pragma once

#ifdef VISION_EXPORTS
#define VISIONDLL_API __declspec(dllexport) 
#else
#define VISIONDLL_API __declspec(dllimport) 
#endif

#include "Algorithm.h"
#include <iostream>

#include <ctime>	// For time() to seed the random number generator.
#include <cstring>	// For memset(), memcpy() and memcmp().
#include <cstdlib>	// For srand() and rand().
#include <cmath>	// For sqrt() and pow().

namespace vis {

	/**
	 * A filter that will create a clusters from an image.
	 */
	class KMeansFilter : public Algorithm {
	public:
		/**
		 * Construct the filter from parameters.
		 * @param  k          The amount of clusters.
		 * @param  iterations The amount of iterations the algorithm will do to optimise the clusters.
		 * @param  verbose    true to print out verbose information, false otherwise.
		 */
		VISIONDLL_API KMeansFilter(int k = 3, int iterations = 25, bool verbose = false);
		/**
		 * Apply the KMeansFilter to the image and put the result in the destination image.
		 * @param image_src The source image to be changed.
		 * @param image_dst The image where the image is to be put in.
		 */
		VISIONDLL_API void ExecuteAlgorithm(Image *image_src, Image *image_dst);
	private:
		/**
		 * The k for this algorithm.
		 */
		int m_K;
		/**
		 * The amount of iterations that the loop will do to optimise the cluster.
		 */
		int m_Iterations;
		/**
		 * Whether verbose information will be printed.
		 */
		bool m_Verbose;
	};

}
