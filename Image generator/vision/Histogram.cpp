#include "stdafx.h"
#include "Histogram.h"

namespace vis {
	template <typename T>
	Histogram<T>::Histogram(unsigned int bins) : m_Bins(bins) {
		m_Hist = new T[bins];
		memset(m_Hist, 0, bins * sizeof(T));
	}
	template <typename T>
	Histogram<T>::~Histogram() {
		delete m_Hist;
	}

	template <typename T>
	void Histogram<T>::WriteAsCSV(const char *file_name) {

		FILE *fptr;
		fopen_s(&fptr, file_name, "w");

		if (fptr == NULL) {
			return;
		}

		for (unsigned int i = 0; i < m_Bins; ++i) {
			fprintf(fptr, "%d;%d\n", i, m_Hist[i]);
		}

		fclose(fptr);

	}

	template <typename T>
	T Histogram<T>::GetMinimum() {
		for (unsigned int i = 0; i < m_Bins; ++i) {
			if (m_Hist[i] > 0) {
				return i;
			}
		}
		return 0;
	}

	template <typename T>
	T Histogram<T>::GetMedian(unsigned int size) {
		int position = size / 2;
		int n = 0;

		for (unsigned int i = 0; i < m_Bins; ++i) {
			n += m_Hist[i];
			if (n >= position) {
				return i;
			}
		}


		return 255;
	}

	template <typename T>
	T Histogram<T>::GetMaximum() {
		for (unsigned int i = m_Bins - 1; i >= 0; --i) {
			if (m_Hist[i] > 0) {
				return i;
			}
		}
		return 0;
	}

	template <typename T>
	T &Histogram<T>::operator[] (int index) {
		return m_Hist[index];
	}
	template class Histogram<unsigned char>;
	template class Histogram<int>;
}