#pragma once

#ifdef VISION_EXPORTS
#define VISIONDLL_API __declspec(dllexport)
#else
#define VISIONDLL_API __declspec(dllimport)
#endif

#include "Image.h"
#include "Matrix.h"
#include <iostream>

namespace vis {

	/**
	 * A class that will use a matrix to transform an image. This transformation class
	 * uses backward mapping. The order can be given as a parameter in the constructor.
	 */
	class Transformation {
	public:
		/**
		 * Construct the Transformation from a matrix and set the order.
		 * @param  matrix The matrix (3x3) that will be used to transform the image.
		 * @param  order  zero-order(0) or first-order(1)
		 */
		VISIONDLL_API Transformation(Matrix *matrix, unsigned short int order);

		/**
		 * Execute the transformation. This will put the result into another image buffer.
		 * This function uses zero-order or first-order.
		 * @param image_src The source image the matrix will be used to get the pixels from.
		 * @param image_dst The destination image that will contain the new locations of pixels.
		 */
		VISIONDLL_API void ExecuteTransformation(Image *image_src, Image *image_dst);
	private:
		/**
		 * The Matrix that is used to map pixels to new locations.
		 */
		Matrix *m_Matrix;
		/**
		 * Zero-order or first-order. Could be a boolean, but we may add more orders in the future.
		 */
		unsigned short int m_Order;
	};

}
