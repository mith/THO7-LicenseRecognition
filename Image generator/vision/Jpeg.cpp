#include "stdafx.h"

#include <stdio.h>	// Defines FILE, needed for libjpeg functions.
#include "jpeglib.h"
#include <cstring>

#include "Jpeg.h"

namespace vis {
	Jpeg::Jpeg(const Jpeg &jpeg) : Image(jpeg.pFileName, 0), m_quality(jpeg.m_quality) {
		this->fields.width = jpeg.fields.width;
		this->fields.height = jpeg.fields.height;
		this->fields.components = jpeg.fields.components;
		this->fields.stride = jpeg.fields.stride;
		this->fields.colorspace = jpeg.fields.colorspace;

		pBuffer = _CreateBuffer(
			this->fields.width,
			this->fields.height,
			this->fields.components);

		memcpy(this->pBuffer, jpeg.pBuffer, this->fields.height * this->fields.width * this->fields.components);
	}
	Jpeg::Jpeg(const char *file_name, int quality, Colorspace cs) : Image(file_name, 0), m_quality(quality) {

		this->fields.width = 0;
		this->fields.height = 0;
		this->fields.components = 0;
		this->fields.stride = 0;
		this->fields.colorspace = cs;

		LoadFromFile();

	}

	Jpeg::Jpeg(unsigned int width, unsigned int height, const char *file_name, int quality, Colorspace cs) : Image(file_name, 0), m_quality(quality) {

		this->fields.width = width;
		this->fields.height = height;
		this->fields.components = cs == RGB ? 3 : 1;
		this->fields.stride = width * this->fields.components;
		this->fields.colorspace = cs;

		pBuffer = _CreateBuffer(
			this->fields.width,
			this->fields.height,
			this->fields.components);

	}

	Jpeg::~Jpeg() {
		_DestroyBuffer(
			pBuffer,
			this->fields.width,
			this->fields.height,
			this->fields.components);
	}

	bool Jpeg::LoadFromFile() {

		struct jpeg_decompress_struct	cinfo;
		struct jpeg_error_mgr			jerr;

		FILE *fptr;
		if ((fptr = fopen(pFileName, "rb")) == NULL) {
			throw std::runtime_error("Couldn't open file for reading");
		}

		cinfo.err = jpeg_std_error(&jerr);
		jpeg_create_decompress(&cinfo);
		jpeg_stdio_src(&cinfo, fptr);
		jpeg_read_header(&cinfo, TRUE);

		cinfo.out_color_space = this->fields.colorspace == RGB ? JCS_RGB : JCS_GRAYSCALE;


		jpeg_start_decompress(&cinfo);


		this->fields.width = cinfo.output_width;
		this->fields.height = cinfo.output_height;
		this->fields.components = cinfo.output_components;
		this->fields.stride = cinfo.output_width * cinfo.output_components;


		pBuffer = _CreateBuffer(cinfo.output_width, cinfo.output_height, cinfo.output_components);


		while (cinfo.output_scanline < cinfo.output_height) {

			JSAMPROW row_address = (JSAMPROW)(pBuffer + this->fields.stride * cinfo.output_scanline);

			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&row_address, 1);

		}

		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);

		fclose(fptr);

		return true;
	}

	bool Jpeg::SaveToFile(const char *file_name) {

		if (file_name == 0) {
			file_name = pFileName;
		}

		struct jpeg_compress_struct	cinfo;
		struct jpeg_error_mgr		jerr;

		JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
		int row_stride;				/* physical row width in image buffer */

		cinfo.err = jpeg_std_error(&jerr);

		jpeg_create_compress(&cinfo);

		FILE *fptr;
		if ((fptr = fopen(file_name, "wb")) == NULL) {
			throw std::runtime_error("Couldn't open file for reading");
		}
		jpeg_stdio_dest(&cinfo, fptr);

		cinfo.image_width = this->fields.width;
		cinfo.image_height = this->fields.height;
		cinfo.input_components = this->fields.components;
		cinfo.in_color_space = this->fields.colorspace == RGB ? JCS_RGB : JCS_GRAYSCALE;

		//cinfo.optimize_coding	= true;
		//cinfo.smoothing_factor = 100;


		jpeg_set_defaults(&cinfo);

		jpeg_set_quality(&cinfo, m_quality, TRUE);

		jpeg_start_compress(&cinfo, TRUE);

		row_stride = cinfo.image_width * cinfo.input_components;

		while (cinfo.next_scanline < cinfo.image_height) {

			row_pointer[0] = (JSAMPROW)(pBuffer + row_stride * cinfo.next_scanline);

			jpeg_write_scanlines(&cinfo, row_pointer, 1);
		}

		jpeg_finish_compress(&cinfo);

		fclose(fptr);

		jpeg_destroy_compress(&cinfo);

		return true;
	}

}