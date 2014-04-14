#include "stdafx.h"
#include "Image.h"

namespace vis {

	Image::Image(const char *file_name, unsigned char *buffer) : pFileName(file_name), pBuffer(buffer) {}

	unsigned char *Image::GetBuffer() { return pBuffer; }

	void Image::ConvertToColorspace(Colorspace new_cs) {
		if (this->fields.colorspace == RGB && new_cs == Grayscale) {

			unsigned char *new_buffer = _CreateBuffer(this->fields.width, this->fields.height, 1, false);

			for (unsigned int y = 0; y < this->fields.height; ++y) {
				for (unsigned int x = 0; x < this->fields.width; ++x) {

					new_buffer[y * this->fields.width + x] = static_cast<unsigned char>(
						0.299 * pBuffer[y * this->fields.stride + x * 3 + 0] +	// Red
						0.587 * pBuffer[y * this->fields.stride + x * 3 + 1] +	// Green
						0.114 * pBuffer[y * this->fields.stride + x * 3 + 2]);	// Blue

				}
			}

			_DestroyBuffer(pBuffer, this->fields.width, this->fields.height, this->fields.components);

			pBuffer = new_buffer;

			this->fields.components = 1;
			this->fields.stride = this->fields.width;
			this->fields.colorspace = Grayscale;

		}
		else if (this->fields.colorspace == Grayscale && new_cs == RGB) {

		}
	}

	unsigned char *Image::_CreateBuffer(int width, int height, int components, bool empty) {

		unsigned char *buffer = new unsigned char[height * width * components];

		if (empty) {
			memset(buffer, 0, height * width * components * sizeof(unsigned char));
		}

		//std::cout << "Buffer with unsigned char*: " << (height * width * components) << std::endl;

		return buffer;

	}
	void Image::_DestroyBuffer(unsigned char *buffer, int width, int height, int components) {

		if (buffer == 0) {
			return;
		}

		delete[] buffer;

	}

}
