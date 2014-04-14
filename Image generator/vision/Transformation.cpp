#include "stdafx.h"
#include "Transformation.h"

#include <math.h>       /* round */

namespace vis {

	Transformation::Transformation(Matrix *matrix, unsigned short int order) : m_Matrix(matrix), m_Order(order) {}

	void Transformation::ExecuteTransformation(Image *image_src, Image *image_dst) {

		if (m_Matrix->size() != 9) {
			return;
		}

		Matrix *inverse = m_Matrix->GetInverse();

		if (m_Order == 0) {	// Zero order

			for (unsigned int y = 0; y < image_dst->fields.height; ++y) {
				for (unsigned int x = 0; x < image_dst->fields.width; ++x) {

					int x_map = (int)round((*inverse)[0] * x + (*inverse)[1] * y + (*inverse)[2]); //x' = a0x + a1y + a2;
					int y_map = (int)round((*inverse)[3] * x + (*inverse)[4] * y + (*inverse)[5]); //y' = b0x + b1y + b2;

					if (x < 0 || y < 0 || x >= (int)image_dst->fields.width || y >= (int)image_dst->fields.height ||
						x_map < 0 || y_map < 0 || x_map >= (int)image_src->fields.width || y_map >= (int)image_src->fields.height) {
						continue;
					}
					image_dst->SetPixel_R(x, y, image_src->GetPixel_R(x_map, y_map));
					image_dst->SetPixel_G(x, y, image_src->GetPixel_G(x_map, y_map));
					image_dst->SetPixel_B(x, y, image_src->GetPixel_B(x_map, y_map));

				}

			}

		} else if (m_Order == 1) {	// First order

			for (unsigned int y = 0; y < image_dst->fields.height; ++y) {
				for (unsigned int x = 0; x < image_dst->fields.width; ++x) {

					float x_map = (*inverse)[0] * x + (*inverse)[1] * y + (*inverse)[2]; //x' = a0x + a1y + a2;
					float y_map = (*inverse)[3] * x + (*inverse)[4] * y + (*inverse)[5]; //y' = b0x + b1y + b2;

					int x0 = (int)floor(x_map);
					int y0 = (int)floor(y_map);
					int x1 = (int)ceil(x_map);
					int y1 = (int)ceil(y_map);

					if ((unsigned int)x1 < image_src->fields.width && x0 >= 0 && (unsigned int)y1 < image_src->fields.height && y0 >= 0) {
						unsigned char rgb[4][3] = {
							{ image_src->GetPixel_R(x0, y0), image_src->GetPixel_G(x0, y0), image_src->GetPixel_B(x0, y0) },
							{ image_src->GetPixel_R(x0, y1), image_src->GetPixel_G(x0, y1), image_src->GetPixel_B(x0, y1) },
							{ image_src->GetPixel_R(x1, y0), image_src->GetPixel_G(x1, y0), image_src->GetPixel_B(x1, y0) },
							{ image_src->GetPixel_R(x1, y1), image_src->GetPixel_G(x1, y1), image_src->GetPixel_B(x1, y1) }
						};

						float x_delta = x_map - x0;
						float y_delta = y_map - y0;

						float p, q;

						p = image_src->GetPixel_R(x0, y0) + x_delta * (image_src->GetPixel_R(x1, y0) - image_src->GetPixel_R(x0, y0));
						q = image_src->GetPixel_R(x0, y1) + x_delta * (image_src->GetPixel_R(x1, y1) - image_src->GetPixel_R(x0, y1));
						image_dst->SetPixel_R(x, y, int(p + y_delta * (q - p)));

						p = image_src->GetPixel_G(x0, y0) + x_delta * (image_src->GetPixel_G(x1, y0) - image_src->GetPixel_G(x0, y0));
						q = image_src->GetPixel_G(x0, y1) + x_delta * (image_src->GetPixel_G(x1, y1) - image_src->GetPixel_G(x0, y1));
						image_dst->SetPixel_G(x, y, int(p + y_delta * (q - p)));

						p = image_src->GetPixel_B(x0, y0) + x_delta * (image_src->GetPixel_B(x1, y0) - image_src->GetPixel_B(x0, y0));
						q = image_src->GetPixel_B(x0, y1) + x_delta * (image_src->GetPixel_B(x1, y1) - image_src->GetPixel_B(x0, y1));
						image_dst->SetPixel_B(x, y, int(p + y_delta * (q - p)));
					}


				}

			}

		}

	}

}