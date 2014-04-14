#include "stdafx.h"
#include "MinimumFilter.h"

#include "Histogram.h"

namespace vis {
	MinimumFilter::MinimumFilter(unsigned int ratio) : pRatio(ratio) {}

	void MinimumFilter::ExecuteAlgorithm(Image *image_src, Image *image_dst) {
		unsigned char *buffer_src = image_src->GetBuffer();
		unsigned char *buffer_dst = image_dst->GetBuffer();

		Histogram<unsigned char> r_hist(256);
		Histogram<unsigned char> g_hist(256);
		Histogram<unsigned char> b_hist(256);

		for (unsigned int y = pRatio; y < image_src->fields.height - pRatio; ++y) {
			for (unsigned int x = pRatio; x < image_src->fields.width - pRatio; ++x) {

				r_hist[image_src->GetPixel_R(x - 1, y - 1)]++;
				r_hist[image_src->GetPixel_R(x - 1, y + 0)]++;
				r_hist[image_src->GetPixel_R(x - 1, y + 1)]++;
				r_hist[image_src->GetPixel_R(x + 0, y - 1)]++;
				r_hist[image_src->GetPixel_R(x + 0, y + 0)]++;
				r_hist[image_src->GetPixel_R(x + 0, y + 1)]++;
				r_hist[image_src->GetPixel_R(x + 1, y - 1)]++;
				r_hist[image_src->GetPixel_R(x + 1, y + 0)]++;
				r_hist[image_src->GetPixel_R(x + 1, y + 1)]++;

				g_hist[image_src->GetPixel_G(x - 1, y - 1)]++;
				g_hist[image_src->GetPixel_G(x - 1, y + 0)]++;
				g_hist[image_src->GetPixel_G(x - 1, y + 1)]++;
				g_hist[image_src->GetPixel_G(x + 0, y - 1)]++;
				g_hist[image_src->GetPixel_G(x + 0, y + 0)]++;
				g_hist[image_src->GetPixel_G(x + 0, y + 1)]++;
				g_hist[image_src->GetPixel_G(x + 1, y - 1)]++;
				g_hist[image_src->GetPixel_G(x + 1, y + 0)]++;
				g_hist[image_src->GetPixel_G(x + 1, y + 1)]++;

				b_hist[image_src->GetPixel_B(x - 1, y - 1)]++;
				b_hist[image_src->GetPixel_B(x - 1, y + 0)]++;
				b_hist[image_src->GetPixel_B(x - 1, y + 1)]++;
				b_hist[image_src->GetPixel_B(x + 0, y - 1)]++;
				b_hist[image_src->GetPixel_B(x + 0, y + 0)]++;
				b_hist[image_src->GetPixel_B(x + 0, y + 1)]++;
				b_hist[image_src->GetPixel_B(x + 1, y - 1)]++;
				b_hist[image_src->GetPixel_B(x + 1, y + 0)]++;
				b_hist[image_src->GetPixel_B(x + 1, y + 1)]++;

				image_dst->SetPixel_R(x, y, r_hist.GetMinimum());
				image_dst->SetPixel_G(x, y, g_hist.GetMinimum());
				image_dst->SetPixel_B(x, y, b_hist.GetMinimum());

				r_hist.clear();
				g_hist.clear();
				b_hist.clear();

			}
		}
	}

}
