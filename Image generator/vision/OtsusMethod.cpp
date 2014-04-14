#include "stdafx.h"
#include "OtsusMethod.h"

namespace vis {

	OtsusMethod::OtsusMethod() {}

	void OtsusMethod::ExecuteAlgorithm(Image *image_src, Image *image_dst) {
		unsigned char *buffer_src = image_src->GetBuffer();
		unsigned char *buffer_dst = image_dst->GetBuffer();

		int histogram[256] = {0};
		for (unsigned int y = 0; y < image_src->fields.height; ++y) {
			for (unsigned int x = 0; x < image_src->fields.width; ++x) {
				histogram[buffer_src[y * image_src->fields.stride + x]]++;
			}
		}

		//if (m_Verbose) { std::cout << "Calculating threshold... "; }

		/**
		 * (C) http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
		 * Modified drastically, but we understand the concept.
		 * We will make our own, perhaps faster, algorithm to get the threshold using
		 * Otsu's method.
		 */

		// Total number of pixels
		int total = image_src->fields.width * image_src->fields.height;

		float sum = 0;
		for (int i = 0; i < 256; ++i) {
			sum += i * histogram[i];
		}

		float total_background = 0;
		int weight_background = 0;
		int weight_foreground = 0;

		float varMax = 0;
		int threshold = 0;

		for (int i = 0; i < 256; ++i) {
			weight_background += histogram[i];

			if (weight_background == 0) {
				continue;
			}

			weight_foreground = total - weight_background;
			if (weight_foreground == 0) {
				break;
			}

			total_background += (float) (i * histogram[i]);

			float mean_background = total_background / weight_background;
			float mean_foreground = (sum - total_background) / weight_foreground;

			// Calculate Between Class Variance
			float varBetween = (float)weight_background * (float)weight_foreground * (mean_background - mean_foreground) * (mean_background - mean_foreground);

			// Check if new maximum found
			if (varBetween > varMax) {
				varMax = varBetween;
				threshold = i;
			}
		}

		//if (m_Verbose) { std::cout << "Found: " << threshold << std::endl; }

		for (unsigned int y = 0; y < image_src->fields.height; ++y) {
			for (unsigned int x = 0; x < image_src->fields.width; ++x) {

				if (buffer_src[y * image_src->fields.stride + x] > threshold) {
					buffer_dst[y * image_src->fields.stride + x] = 0;
				} else {
					buffer_dst[y * image_src->fields.stride + x] = 255;
				}

			}
		}

	}

}
