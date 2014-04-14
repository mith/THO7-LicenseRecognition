#include "stdafx.h"
#include "SaltAndPepperNoise.h"
#include <cstdlib>	// For srand() and rand().

namespace vis {

	SaltAndPepperNoise::SaltAndPepperNoise(unsigned int probability) : pProbability(probability) {}

	void SaltAndPepperNoise::ExecuteAlgorithm(Image *image_src, Image *image_dst) {

		if (!pProbability) {
			return;
		}

		for (unsigned int y = 0; y < image_src->fields.height; ++y) {
			for (unsigned int x = 0; x < image_src->fields.width; ++x) {

				// Roughly a chance of pProbability % it will put noise here.
				// Else it will just put the normal pixel there.
				if (rand() % (100 / pProbability) == 0) {
					// Roughly a chance of 1/2 it will be black, or white.
					if (rand() % 2 == 0) {
						image_dst->SetPixel_R(x, y, 0);
						image_dst->SetPixel_G(x, y, 0);
						image_dst->SetPixel_B(x, y, 0);
					}
					else {
						image_dst->SetPixel_R(x, y, 255);
						image_dst->SetPixel_G(x, y, 255);
						image_dst->SetPixel_B(x, y, 255);
					}
				}
				else {
					image_dst->SetPixel_R(x, y, image_src->GetPixel_R(x, y));
					image_dst->SetPixel_G(x, y, image_src->GetPixel_G(x, y));
					image_dst->SetPixel_B(x, y, image_src->GetPixel_B(x, y));
				}

			}
		}
	}

}
