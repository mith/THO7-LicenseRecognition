/*! 
 *  \brief     The main function that is to be executed, which will start and generate
 *  'imperfect' images from source images.
 *  \details	All functions and all lines of codes are made by the same person.
 *  \author    Benno Zeeman
 *  \version   1.4
 *  \date      March 2014
 */

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

#include <cstdlib>	// For srand() and rand().

#include <vision/Image.h>
#include <vision/Jpeg.h>

#include <vision/Transformation.h>
#include <vision/Matrix.h>

#include <vision/Algorithm.h>
#include <vision/MinimumFilter.h>
#include <vision/MedianFilter.h>
#include <vision/MaximumFilter.h>
#include <vision/SaltAndPepperNoise.h>


// Function that will calculate optimal dimensions from image when transformation applied.
// Will also return a translation matrix that will shift the image into visible space.
vis::Matrix *calculate_dimensions(
	unsigned int width,		// Dimensions of image whereover matrix is applied.
	unsigned int height,
	vis::Matrix *matrix,	// Matrix to be used as transformation
	unsigned int &newWidth,	// New dimensions that the transformed image can fit into.
	unsigned int &newHeight)
{
	// This function will take the corners of the transformed image,
	// take the dimensions of the bounding box (the space needed for the image to fit in)
	// and create a translation matrix that will shift the image into the box.
	int corners[4][2] =
	{
		{
			(int)round((*matrix)[0] * 0 + (*matrix)[1] * 0 + (*matrix)[2]),
			(int)round((*matrix)[3] * 0 + (*matrix)[4] * 0 + (*matrix)[5])
		},
		{
			(int)round((*matrix)[0] * (width - 1) + (*matrix)[1] * 0 + (*matrix)[2]),
			(int)round((*matrix)[3] * (width - 1) + (*matrix)[4] * 0 + (*matrix)[5])
		},
		{
			(int)round((*matrix)[0] * 0 + (*matrix)[1] * (height - 1) + (*matrix)[2]),
			(int)round((*matrix)[3] * 0 + (*matrix)[4] * (height - 1) + (*matrix)[5])
		},
		{
			(int)round((*matrix)[0] * (width - 1) + (*matrix)[1] * (height - 1) + (*matrix)[2]),
			(int)round((*matrix)[3] * (width - 1) + (*matrix)[4] * (height - 1) + (*matrix)[5])
		}
	};
	int min_max[2][2] = { { corners[0][0], corners[0][1] }, { corners[0][0], corners[0][1] } };

	for (unsigned int i = 1; i < 4; ++i) {
		if (min_max[0][0] > corners[i][0]) {
			min_max[0][0] = corners[i][0];
		}
		if (min_max[0][1] > corners[i][1]) {
			min_max[0][1] = corners[i][1];
		}
		if (min_max[1][0] < corners[i][0]) {
			min_max[1][0] = corners[i][0];
		}
		if (min_max[1][1] < corners[i][1]) {
			min_max[1][1] = corners[i][1];
		}
	}
	newWidth = min_max[1][0] - min_max[0][0];
	newHeight = min_max[1][1] - min_max[0][1];

	// Create the translation matrix in a float array.
	float *matrix_raw = new float[9];
	matrix_raw[0] = 1.f; matrix_raw[1] = 0.f; matrix_raw[2] = 0.f - min_max[0][0];
	matrix_raw[3] = 0.f; matrix_raw[4] = 1.f; matrix_raw[5] = 0.f - min_max[0][1];
	matrix_raw[6] = 0.f; matrix_raw[7] = 0.f; matrix_raw[8] = 1.f;

	return new vis::Matrix(3, 3, matrix_raw);
}

/* FUNCTIONS TO GET FILE NAMES FROM DIRECTORY */
std::string wchar_t2string(const wchar_t *wchar)
{
	std::string str = "";
	int index = 0;
	while (wchar[index] != 0) {
		str += (char)wchar[index];
		++index;
	}
	return str;
}
wchar_t *string2wchar_t(const std::string &str)
{
	wchar_t wchar[260];
	int index = 0;
	while (index < str.size()) {
		wchar[index] = (wchar_t)str[index];
		++index;
	}
	wchar[index] = 0;
	return wchar;
}
std::vector<std::string> listFilesInDirectory(std::string directoryName)
{
	WIN32_FIND_DATA FindFileData;
	wchar_t * FileName = string2wchar_t(directoryName);
	HANDLE hFind = FindFirstFile(FileName, &FindFileData);

	std::vector<std::string> listFileNames;
	listFileNames.push_back(wchar_t2string(FindFileData.cFileName));

	while (FindNextFile(hFind, &FindFileData)) {
		listFileNames.push_back(wchar_t2string(FindFileData.cFileName));
	}

	return listFileNames;
}

vis::Jpeg *crop_image(vis::Jpeg *image_src, bool horizontally = true)
{

	int min_max_coordinates[2][2] = { { -1, -1 }, { -1, -1 } };



	for (unsigned int y = 0; y < image_src->fields.height; ++y) {
		for (unsigned int x = 0; x < image_src->fields.width; ++x) {
			if (image_src->GetPixel_R(x, y) > 128 &&
				image_src->GetPixel_G(x, y) > 128 &&
				image_src->GetPixel_B(x, y) > 128) {
				continue;
			}

			if (min_max_coordinates[0][0] == -1) {
				min_max_coordinates[0][0] = x;
				min_max_coordinates[0][1] = y;

				//std::cout << "(" << (int)image_src->GetPixel_R(x, y) << "," << (int)image_src->GetPixel_G(x, y) << "," << (int)image_src->GetPixel_B(x, y) << ")" << std::endl;
			}
			else {
				if (x < min_max_coordinates[0][0]) {
					min_max_coordinates[0][0] = x;
				}
				if (y < min_max_coordinates[0][1]) {
					min_max_coordinates[0][1] = y;
				}
			}

			if (min_max_coordinates[1][0] == -1) {
				min_max_coordinates[1][0] = x;
				min_max_coordinates[1][1] = y;
			}
			else {
				if (x > min_max_coordinates[1][0]) {
					min_max_coordinates[1][0] = x;
				}
				if (y > min_max_coordinates[1][1]) {
					min_max_coordinates[1][1] = y;
				}
			}
		}
	}
	if (!horizontally) {
		min_max_coordinates[0][1] = 0;
		min_max_coordinates[1][1] = image_src->fields.height - 1;
	}
	//std::cout << "(" << min_max_coordinates[0][0] << "," << min_max_coordinates[0][1] << ")" << std::endl;
	//std::cout << "(" << min_max_coordinates[1][0] << "," << min_max_coordinates[1][1] << ")" << std::endl;

	unsigned int newWidth = min_max_coordinates[1][0] - min_max_coordinates[0][0] + 1;
	unsigned int newHeight = min_max_coordinates[1][1] - min_max_coordinates[0][1] + 1;

	vis::Jpeg *ptr = new vis::Jpeg(newWidth, newHeight, "", 100, vis::Jpeg::RGB);

	for (unsigned int y = 0; y < newHeight; ++y) {
		for (unsigned int x = 0; x < newWidth; ++x) {
			ptr->SetPixel_R(x, y, image_src->GetPixel_R(x + min_max_coordinates[0][0], y + min_max_coordinates[0][1]));
			ptr->SetPixel_G(x, y, image_src->GetPixel_G(x + min_max_coordinates[0][0], y + min_max_coordinates[0][1]));
			ptr->SetPixel_B(x, y, image_src->GetPixel_B(x + min_max_coordinates[0][0], y + min_max_coordinates[0][1]));
		}
	}

	return ptr;
}

int main(int argc, char *argv[])
{
	// Seed the generator
	srand(static_cast<unsigned int>(time(NULL)));

	// String vector containing file names of certain directory.
	std::vector<std::string> listFiles;
	// All Jpeg images that are loaded from the directory.
	std::vector<vis::Jpeg *> images_src;
	// Put all the files listed in the directory into the vector.
	listFiles = listFilesInDirectory("./images/source/*.jpg");

	// Loop for each file and make the Jpeg Image objects.
	for each (std::string file in listFiles) {
		std::string full_path = "./images/source/" + file;

		vis::Jpeg *image_src = new vis::Jpeg(full_path.c_str(), 100, vis::Jpeg::RGB);

		// Fit the character image in an optimal box.
		if (file[0] == '-') {
			images_src.push_back(crop_image(image_src, false));
		}
		else {
			images_src.push_back(crop_image(image_src));
		}
		delete image_src;
	}

	std::cout << "Editing " << images_src.size() << " images";
	unsigned int total_images_count = 0;

	// Loop for every Image, execute random filters and save the file.
	for (unsigned int i = 0; i < images_src.size(); ++i) {

		// Loop 100 times for every image.
		for (unsigned int j = 0; j < 100; ++j) {
			// Feedback to display on the end of the program.
			total_images_count++;

			// Scale the image randomly. The originals usually are 50x50, but we want different sizes.
			vis::Matrix matrix_scale(3, 3);
			float scale = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / .7f)) + .3f;
			matrix_scale[0] = scale; matrix_scale[1] = 0.0f; matrix_scale[2] = 0.0f;
			matrix_scale[3] = 0.0f; matrix_scale[4] = scale; matrix_scale[5] = 0.0f;
			matrix_scale[6] = 0.0f; matrix_scale[7] = 0.0f; matrix_scale[8] = 1.0f;

			vis::Matrix matrix_shear(3, 3);
			// Create a transformation matrix_shear with random x and y shears. Between -.1 and 1.
			// This will make the image a little bit unsharper on some edges etc.
			matrix_shear[0] = 1; matrix_shear[1] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / .3f)) - .15f; matrix_shear[2] = 0;
			matrix_shear[3] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / .3f)) - .15f; matrix_shear[4] = 1; matrix_shear[5] = 0;
			matrix_shear[6] = 0; matrix_shear[7] = 0; matrix_shear[8] = 1;

			// Combine the matrices.
			vis::Matrix matrix_combined = matrix_shear * matrix_scale;

			// Calculate matrix that will shift the image into a fitting image with the new width and new size.
			unsigned int newWidth, newHeight;
			vis::Matrix *matrix_translate = calculate_dimensions(images_src[i]->fields.width, images_src[i]->fields.height, &matrix_combined, newWidth, newHeight);

			// Create two temporary images that will hold the intermediate results of the filters.
			vis::Jpeg *image_dst1 = new vis::Jpeg(newWidth, newHeight, "", 100, vis::Jpeg::RGB);
			vis::Jpeg *image_dst2 = new vis::Jpeg(newWidth, newHeight, "", 100, vis::Jpeg::RGB);

			// Make the complete image white.
			memset(image_dst1->GetBuffer(), 255, image_dst1->fields.height * image_dst1->fields.stride);
			memset(image_dst2->GetBuffer(), 255, image_dst2->fields.height * image_dst2->fields.stride);

			// Get the final matrix.
			vis::Matrix total_matrix = (*matrix_translate) * matrix_combined;

			// Transform the matrix, applying the rotation and shear.
			vis::Transformation scale_trans(&total_matrix, 1);
			scale_trans.ExecuteTransformation(images_src[i], image_dst2);

			// The random number that will be used to determine wether we will apply a filter.
			int rand_bumber;
			if (image_dst2->fields.width > 24 && image_dst2->fields.height > 24) {

				if ((rand_bumber = rand() / (RAND_MAX / 2)) == 0) {
					// Apply a median filter to distort some fine edges etc.
					vis::MinimumFilter algo_min(rand_bumber + 1);
					algo_min.ExecuteAlgorithm(image_dst2, image_dst1);

					// Apply a median filter to distort some fine edges etc.
					vis::MaximumFilter algo_max(rand_bumber + 1);
					algo_max.ExecuteAlgorithm(image_dst1, image_dst2);
				}

				// Apply some salt and pepper, 10% - 30%
				vis::SaltAndPepperNoise algo_sap(rand() / (RAND_MAX / 15) + 0);
				algo_sap.ExecuteAlgorithm(image_dst2, image_dst1);

				// Apply a median filter to distort some fine edges etc.
				vis::MedianFilter algo_median(rand() / (RAND_MAX / 3) + 1);
				algo_median.ExecuteAlgorithm(image_dst1, image_dst2);
			}

			// Determine file name.
			char dig[4];
			_itoa_s(j, dig, 10);
			std::string save_as = "./images/" + listFiles[i];
			size_t pos;
			if ((pos = save_as.find_last_of('.')) != std::string::npos) {
				save_as.insert(pos, dig);
			}

			image_dst2->SaveToFile(save_as.c_str());

			delete image_dst1;
			delete image_dst2;
			delete matrix_translate;
		}
		std::string save_as = "./images/" + listFiles[i];
		images_src[i]->SaveToFile(save_as.c_str());

		std::cout << '.';

	}
	std::cout << " done. " << total_images_count << " images saved." << std::endl;

	for (vis::Jpeg *image_src : images_src) {
		delete image_src;
	}

	std::cout << "Press enter to continue..."; std::cin.ignore();

	return 0;
}