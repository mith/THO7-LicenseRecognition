#pragma once

#ifdef VISION_EXPORTS
#define VISIONDLL_API __declspec(dllexport) 
#else
#define VISIONDLL_API __declspec(dllimport) 
#endif

#include "Algorithm.h"
#include <iostream>

namespace vis {

	class MedianFilter : public Algorithm {
	public:

		// Medianfilter
		//
		// This function creates the class, the class constructor.
		// It initializes the class with the initalization list, instead of a body.
		VISIONDLL_API MedianFilter(unsigned int ratio);
		
		// ExecuteAlgorithm
		//
		// This function needs to be defined, since the abstract Algorithm class is included in this class.
		// The function is called with a pointer to the source image, and a pointer to the destination image.
		// From there on it will execute the MedianFilter algorithm, and edit the actual data in image_dst
		// so no return value is required.
		VISIONDLL_API void ExecuteAlgorithm(Image *image_src, Image *image_dst);
	private:
		// pRatio
		//
		// This local/private variable is necessary in order for the 'for' loop in the ExecuteAlgorithm to work
		// properly. It makes sure the kernel doesn't go out of it's images bounds, by limiting the 
		// pixels checked by the 'radius' of the kernel. For example, if a 3x3 kernel is used, the radius
		// would be '1'. In that way, the filter will start checking with it's kernel at pixel 1,1 instead
		// of pixel 0,0 and resulting in non-existent pixels.
		int pRatio;
	};

}
