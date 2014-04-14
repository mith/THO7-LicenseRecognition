#pragma once

#ifdef VISION_EXPORTS
#define VISIONDLL_API __declspec(dllexport) 
#else
#define VISIONDLL_API __declspec(dllimport) 
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

namespace vis {

	class Image {
	public:
		VISIONDLL_API Image(const char *pFileName, unsigned char *buffer);
		/**
		* Colorspaces that are possibly used in this class.
		*/
		enum Colorspace {
			RGB,
			Grayscale
		};
		/**
		* Data from the image that is in the buffer.
		*/
		struct Fields {
			unsigned int	width;
			unsigned int	height;
			unsigned int	stride;
			unsigned int	components;

			Colorspace		colorspace;
		} fields;

		/**
		* Will decompress the picture that should be loaded from the file.
		* @return Returns false on failure, true otherwise.
		*/
		virtual VISIONDLL_API bool LoadFromFile() = 0;
		/**
		* Compress the image data to a jpg file format.
		* @param  quality An int from 0-100, 0 means worst, 100 means best.
		* @return         Returns false on failure.
		*/
		virtual VISIONDLL_API bool SaveToFile(const char *file_name = 0) = 0;
		/**
		* This function will give the pointer to the buffer of the image data.
		* @return A pointer to the buffer.
		*/
		VISIONDLL_API unsigned char *GetBuffer();

		VISIONDLL_API void ConvertToColorspace(Colorspace new_cs);

		inline VISIONDLL_API unsigned char GetPixel(unsigned x, unsigned y) { return pBuffer[y * fields.stride + x * fields.components]; }
		inline VISIONDLL_API unsigned char GetPixel_R(unsigned x, unsigned y) { return pBuffer[y * fields.stride + x * fields.components + 0]; }
		inline VISIONDLL_API unsigned char GetPixel_G(unsigned x, unsigned y) { return pBuffer[y * fields.stride + x * fields.components + 1]; }
		inline VISIONDLL_API unsigned char GetPixel_B(unsigned x, unsigned y) { return pBuffer[y * fields.stride + x * fields.components + 2]; }

		inline VISIONDLL_API void SetPixel(unsigned x, unsigned y, unsigned char v) { pBuffer[y * fields.stride + x * fields.components] = v; }
		inline VISIONDLL_API void SetPixel_R(unsigned x, unsigned y, unsigned char v) { pBuffer[y * fields.stride + x * fields.components + 0] = v; }
		inline VISIONDLL_API void SetPixel_G(unsigned x, unsigned y, unsigned char v) { pBuffer[y * fields.stride + x * fields.components + 1] = v; }
		inline VISIONDLL_API void SetPixel_B(unsigned x, unsigned y, unsigned char v) { pBuffer[y * fields.stride + x * fields.components + 2] = v; }
	protected:
		/**
		* char array containing the name of the file the image comes from
		* and/or will be put in at compression.
		*/
		const char *pFileName;
		/**
		* Pointer to buffer containing image data.
		*/
		unsigned char *pBuffer;

		/**
		* Create a buffer to hold the image data.
		* @param  width      The width  of the image in pixels
		* @param  height     The height of the image in pixels
		* @param  components The amount of components per pixel
		* @param  empty      If true, all data will be set on 0 initially.
		* @return            Will return a pointer to the buffer.
		*/
		unsigned char	*_CreateBuffer(int width, int height, int components = 3, bool empty = true);
		/**
		* Destroy a buffer that has been made with _CreateBuffer
		* @param  buffer     A pointer to the buffer that is to be destroyed.
		* @param  width      The width of the image in pixels
		* @param  height     The height of the image in pixels
		* @param  components The amount of components per pixel
		*/
		void			_DestroyBuffer(unsigned char *buffer, int width, int height, int components = 3);
	};

}
