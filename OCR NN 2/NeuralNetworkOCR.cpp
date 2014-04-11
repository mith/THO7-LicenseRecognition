#include "NeuralNetworkOCR.h"
#include "CheckPatterns.h"
#include "ImageList.h"


NeuralNetworkOCR::NeuralNetworkOCR() 
: neural_network(std::vector<unsigned int>{38, 50, 36})
{
}

NeuralNetworkOCR::NeuralNetworkOCR(const std::string & importFile)
: neural_network(importFile)
{

}

NeuralNetworkOCR::~NeuralNetworkOCR()
{
}

std::pair<char, double> NeuralNetworkOCR::convert(const ImageGray & img)
{
	auto input = img_to_input(img);

	neural_network.feedForward(input);

	// TODO: calculate percentage

	return { output_to_char(neural_network.getOutput()), 1.0f };
}

const std::vector<double> & NeuralNetworkOCR::output_nodes() const
{
	return neural_network.getOutput();
}

void NeuralNetworkOCR::train(const ImageList & images, int passes)
{
	for (int pass = 0; pass < passes; pass++) {
		auto img_data = images.getRandom();

		auto input = img_to_input(img_data.image);

		neural_network.feedForward(input);

		neural_network.backPropagate(char_to_output(img_data.getChar()));
	}
}

std::vector<double> NeuralNetworkOCR::img_to_input(const ImageGray & img)
{
	std::vector<double> input {
		patterns.countBlackPixelsPerRowHorizontal(img, 10),
		patterns.countBlackPixelsPerRowHorizontal(img, 20),
		patterns.countBlackPixelsPerRowHorizontal(img, 30),
		patterns.countBlackPixelsPerRowHorizontal(img, 40),
		patterns.countBlackPixelsPerRowHorizontal(img, 50),
		patterns.countBlackPixelsPerRowHorizontal(img, 60),
		patterns.countBlackPixelsPerRowHorizontal(img, 70),
		patterns.countBlackPixelsPerRowHorizontal(img, 80),
		patterns.countBlackPixelsPerRowHorizontal(img, 90),
		
		patterns.countBlackPixelsPerLineVertical(img, 10),
		patterns.countBlackPixelsPerLineVertical(img, 20),
		patterns.countBlackPixelsPerLineVertical(img, 30),
		patterns.countBlackPixelsPerLineVertical(img, 40),
		patterns.countBlackPixelsPerLineVertical(img, 50),
		patterns.countBlackPixelsPerLineVertical(img, 60),
		patterns.countBlackPixelsPerLineVertical(img, 70),
		patterns.countBlackPixelsPerLineVertical(img, 80),
		patterns.countBlackPixelsPerLineVertical(img, 90),

		patterns.checkSymmetryVertical(img),
		patterns.checkSymmetryHorizontal(img),
		
		patterns.countBlackWhiteTransisitionHorizontal(img, 10),
		patterns.countBlackWhiteTransisitionHorizontal(img, 20),
		patterns.countBlackWhiteTransisitionHorizontal(img, 30),
		patterns.countBlackWhiteTransisitionHorizontal(img, 40),
		patterns.countBlackWhiteTransisitionHorizontal(img, 50),
		patterns.countBlackWhiteTransisitionHorizontal(img, 60),
		patterns.countBlackWhiteTransisitionHorizontal(img, 70),
		patterns.countBlackWhiteTransisitionHorizontal(img, 80),
		patterns.countBlackWhiteTransisitionHorizontal(img, 90),
		
		patterns.countBlackWhiteTransisitionVertical(img, 10),
		patterns.countBlackWhiteTransisitionVertical(img, 20),
		patterns.countBlackWhiteTransisitionVertical(img, 30),
		patterns.countBlackWhiteTransisitionVertical(img, 40),
		patterns.countBlackWhiteTransisitionVertical(img, 50),
		patterns.countBlackWhiteTransisitionVertical(img, 60),
		patterns.countBlackWhiteTransisitionVertical(img, 70),
		patterns.countBlackWhiteTransisitionVertical(img, 80),
		patterns.countBlackWhiteTransisitionVertical(img, 90),
	};

	return input;
}

char NeuralNetworkOCR::output_to_char(const std::vector<double> & output)
{
	unsigned int highest = 0;
	for (unsigned int i = 1; i < output.size() - 1; ++i) {
		if (output[i] > output[highest]) {
			highest = i;
		}
	}
	if (highest < 10) {
		return highest + 48;
	}
	else {
		return highest + 55;
	}
}

std::vector<double> NeuralNetworkOCR::char_to_output(char c)
{
	std::vector<double> output(36, -1.0f);

	if (c > 47 && c < 58) {
		output[c - 48] = 1.0; // Numbers 0-9 in indices 0-9
	}
	else if (c > 64 && c < 91) {
		output[c - 55] = 1.0; // Characters A-Z in indices 10-35
	}
	else if (c > 96 && c < 123) {
		output[c - 87] = 1.0;
	}
	return output;
}

void NeuralNetworkOCR::export(std::string filename) const
{
	neural_network.exportNetwork(filename);
}