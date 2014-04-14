#include "stdafx.h"
#include "KMeansFilter.h"

namespace vis {

	KMeansFilter::KMeansFilter(int k, int iterations, bool verbose) : m_K(k), m_Iterations(iterations), m_Verbose(verbose) {
		// Seed the random number generator
		srand(static_cast<unsigned int>(time(NULL)));
	}

	void KMeansFilter::ExecuteAlgorithm(Image *image_src, Image *image_dst) {
		unsigned char *buffer_src = image_src->GetBuffer();
		unsigned char *buffer_dst = image_dst->GetBuffer();

		// clusters_size is used to keep track of how many pixels are added into a cluster.
		// clusters_mean is used to keep the RGB values of the mean of the cluster.
		// clusters_values is used to calculate the new mean of a cluster. Example: RED = clusters_values[x][0]/clusters_size[x]
		unsigned int *clusters_size = new unsigned int[m_K]; memset(clusters_size, 0, m_K * sizeof(unsigned int));
		unsigned char **clusters_mean = new unsigned char*[m_K];
		unsigned long long int **clusters_values = new unsigned long long int*[m_K];


		if (m_Verbose) { std::cout << "Finding initial means"; }
		// Find random means to work on.
		for (int i = 0; i < m_K; ++i) {

			// Pick pseudo-random coordinates as the centre of a cluster.
			int x = int(float(rand()) / RAND_MAX * image_src->fields.width);
			int y = int(float(rand()) / RAND_MAX * image_src->fields.height);

			// Create a space to hold the total values of all R, G and B channels, so we can calculate the average from
			// that as the new mean of a cluster, in future.
			clusters_values[i] = new unsigned long long int[3];
			memset(clusters_values[i], 0, 3 * sizeof(unsigned long long int));

			// Put the RGB values of the randomly picked centre as the new mean of this cluster.
			clusters_mean[i] = new unsigned char[3];
			memcpy(clusters_mean[i], buffer_src + image_src->fields.stride * y + x * image_src->fields.components, 3 * sizeof(unsigned char));

			if (m_Verbose) { std::cout << '.'; }

		}
		if (m_Verbose) { std::cout << std::endl << "Finding new means"; }

		int iterations;
		// Loop for a max amount of time. Every loop will optimize the clusters.
		// When the same means are found, this loop will break.
		for (iterations = 0; iterations < m_Iterations; ++iterations) {

			// Loop over every pixel, determining the best cluster.
			for (unsigned int y = 0; y < image_src->fields.height; ++y) {
				for (unsigned int x = 0; x < image_src->fields.width; ++x) {

					// Maximum distance possible
					double closest_cluster_distance = sqrt(pow(256 - 0, 2) + pow(256 - 0, 2) + pow(256 - 0, 2)) + 1;
					// The cluster we will put this pixel into.
					int closest_cluster = -1;

					// The RGB values of the current pixel
					unsigned char *rgb = buffer_src + image_src->fields.stride * y + x * image_src->fields.components;

					// Loop over every cluster, so we can pick the closest mean.
					for (int i = 0; i < m_K; ++i) {

						// Put the RGB values of the mean of this cluster into this pointer.
						unsigned char *mean = clusters_mean[i];

						// Calculate the distance to the mean of the cluster.
						double distance = sqrt(pow(rgb[0] - mean[0], 2) + pow(rgb[1] - mean[1], 2) + pow(rgb[2] - mean[2], 2));

						// Check if the distance is shorter than before. If so, we found a closer centre.
						if (distance < closest_cluster_distance) {

							// The new (smaller) distance.
							closest_cluster_distance = distance;

							// The cluster that we should add the pixel to, as yet.
							closest_cluster = i;

						}

					}

					// Add the RGB values into the cluster.
					clusters_values[closest_cluster][0] += rgb[0];
					clusters_values[closest_cluster][1] += rgb[1];
					clusters_values[closest_cluster][2] += rgb[2];

					// Add one to the total size of the cluster.
					clusters_size[closest_cluster]++;

				}
			}
			// This bool will represent the fact that the same means are found, unless proven otherwise.
			bool same_means = true;
			// Loop for every cluster to calculate the new mean of a the cluster.
			for (int i = 0; i < m_K; ++i) {

				//std::cout << std::endl << "clusters_size[" << i << "] = " << clusters_size[i] << std::endl;

				if (clusters_size[i] == 0) {
					continue;
				}
				// Get the new averages of the channels and use them as new centre values.
				unsigned char *new_mean_rgb = new unsigned char[3];
				new_mean_rgb[0] = (unsigned char)(clusters_values[i][0] / clusters_size[i]);
				new_mean_rgb[1] = (unsigned char)(clusters_values[i][1] / clusters_size[i]);
				new_mean_rgb[2] = (unsigned char)(clusters_values[i][2] / clusters_size[i]);

				// If the centers are the same, we may break and preserve the vector.
				if (memcmp(new_mean_rgb, clusters_mean[i], 3 * sizeof(unsigned char)) != 0) {

					// The means aren't the same, so we will keep looping.
					same_means = false;

					// Free the memory of the old mean RGB.
					delete[] clusters_mean[i];

					// Put the new mean into the cluster mean.
					clusters_mean[i] = new_mean_rgb;

				}

				// Put the size counter on 0, so we can calculate the right values next time again.
				clusters_size[i] = 0;
				// Put the total channel values on 0, so we can find an 'optimized' mean next time.
				memset(clusters_values[i], 0, 3 * sizeof(unsigned long long int));

			}

			if (m_Verbose) { std::cout << '.'; }

			// If this boolean is still true, it means every cluster didn't have their means changed, so any further
			// loops wouldn't make sense. Print a star, so we know it found a mean under MAX_ITERATIONS.
			if (same_means) {
				break;
			}
		}

		if (m_Verbose) { std::cout << " with " << iterations << "/" << m_Iterations << " iterations." << std::endl << "Setting pixels to closest cluster... "; }

		// Set all pixels in the image to the optimized means of the clusters.
		for (unsigned int y = 0; y < image_src->fields.height; ++y) {
			for (unsigned int x = 0; x < image_src->fields.width; ++x) {

				// Maximum distance possible
				double closest_cluster_distance = sqrt(pow(256 - 0, 2) + pow(256 - 0, 2) + pow(256 - 0, 2)) + 1;
				// The cluster we will put this pixel into.
				int closest_cluster = -1;

				// The RGB values of the current pixel
				unsigned char *rgb = buffer_src + image_src->fields.stride * y + x * image_src->fields.components;

				// Loop over every cluster to find the closest to the current pixel
				for (int i = 0; i < m_K; ++i) {

					unsigned char *mean = clusters_mean[i];

					double distance = sqrt(pow(rgb[0] - mean[0], 2) + pow(rgb[1] - mean[1], 2) + pow(rgb[2] - mean[2], 2));

					if (distance < closest_cluster_distance) {

						closest_cluster_distance = distance;

						closest_cluster = i;

					}

				}

				// Set the pixel to the mean of the cluster.
				rgb = clusters_mean[closest_cluster];
				memcpy(buffer_dst + image_src->fields.stride * y + x * image_src->fields.components, rgb, 3 * sizeof(unsigned char));

			}
		}
		if (m_Verbose) { std::cout << "Done" << std::endl; }
		for (int i = 0; i < m_K; ++i) {
			delete[] clusters_mean[i];
			delete[] clusters_values[i];

		}
		delete[]	clusters_size;
		delete[]	clusters_mean;
		delete[]	clusters_values;
	}

}
