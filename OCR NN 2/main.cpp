#include <vector>
#include "NeuralNetwork.h"
#include "basetimer.h"
#include "ImageLib.h"
#include "OCRImageData.h"
#include <ctime>


int main(int argc, const char* argv[])
{
	std::string img_dir = argv[1];
	OCRImageData trainingData(img_dir);
	std::vector<unsigned int> topology = trainingData.getTopology();
	std::vector<float> input(topology.front());
	std::vector<float> output(topology.back());
	std::vector<float> targets(topology.back());
	int num_images = trainingData.loadImageList();
	srand(std::time(0));

	//NeuralNetwork net(topology);
	NeuralNetwork net("./Export/OCR.txt");

	/*for (int pass = 0; pass < 1 * 1000 * 1000; pass++) {
		int cur_img = (rand() * (int)(num_images - 1) / RAND_MAX);
		trainingData.getNextInputs(input, cur_img);
		trainingData.getTargetOutputs(targets, cur_img);
		net.feedForward(input);
		net.backPropagate(targets);
	}*/
	unsigned int success = 0;
	//net.exportNetwork("./Export/OCR.txt");
	for (int pass = 0; pass < 1000; pass++) {
		int cur_img = (rand() * (int)(num_images - 1) / RAND_MAX);
		trainingData.getTargetOutputs(targets, cur_img);
		trainingData.getNextInputs(input, cur_img);
		net.feedForward(input);
		output = net.getOutput();
		std::cout << "Target char: " << trainingData.imageData[cur_img] << std::endl;
		std::cout << "Output char: " << trainingData.getCharFromOutputs(output) << std::endl << std::endl;
		if (trainingData.getCharFromOutputs(output)[0] == trainingData.imageData[cur_img]) {
			success++;
		}
	}
	std::cout << "Times success out of 1000 passes: " << success;
	std::cin.ignore();
	return 0;
}