#pragma once

#ifdef VISION_EXPORTS
#define VISIONDLL_API __declspec(dllexport) 
#else
#define VISIONDLL_API __declspec(dllimport) 
#endif

#include <cstring>	// For memset(), memcpy() and memcmp().
#include <cstdio>
#include <iostream>

namespace vis {
	/**
	 * Template class that is able to hold histograms bins with values.
	 */
	template <typename T>
	class Histogram {
	public:
		/**
		 * Create a histogram with a couple of bins.
		 * @param  bins The amount of bins, defaults to 256.
		 */
		VISIONDLL_API Histogram(unsigned int bins = 256);
		VISIONDLL_API ~Histogram();

		/**
		 * Write the histogram to a comma separated file.
		 * @param file_name The file name of the file to write into.
		 */
		VISIONDLL_API void WriteAsCSV(const char *file_name);
		/**
		 * Get the minimum bin that has a value of the histogram.
		 * @return Return the minimum value.
		 */
		VISIONDLL_API T GetMinimum();
		/**
		 * Get the median from the histogram.
		 * @param  size The amount of values in the histogram.
		 * @return      The median.
		 */
		VISIONDLL_API T GetMedian(unsigned int size);
		/**
		 * Get the maximum bin that has a value of the histogram.
		 * @return Return the maximum value.
		 */
		VISIONDLL_API T GetMaximum();

		/**
		 * Subscript operator to change bins values.
		 * @param  index [description]
		 * @return       [description]
		 */
		VISIONDLL_API T &operator[](int index);

		VISIONDLL_API void clear() { memset(m_Hist, 0, m_Bins * sizeof(T)); }
		/**
		 * Return the amount of bins
		 * @return Amount of bins.
		 */
		inline VISIONDLL_API unsigned int length() { return m_Bins; }
	private:
		T *m_Hist;
		unsigned int m_Bins;
	};

}
