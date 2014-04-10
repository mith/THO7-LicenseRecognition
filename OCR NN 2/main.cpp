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

	NeuralNetwork net(topology);
	

	BaseTimer tmr;
	tmr.start();


	int num_images = trainingData.loadImageList();

	std::vector<float> input(topology.front(), 0.88f);
	std::vector<float> output(topology.back());
	std::vector<float> targets(topology.back());

	srand(std::time(0));

	for (int pass = 0; pass < 1 * 1000* 1000; pass++) {
		int cur_img = (rand() * (int)(num_images - 1) / RAND_MAX);
		trainingData.getNextInputs(input, cur_img);
		trainingData.getTargetOutputs(targets, cur_img);
		net.feedForward(input);
		net.backPropagate(targets);
	}
	tmr.stop();

	std::cout << "training took: " << tmr.elapsedSeconds() << std::endl;
	tmr.reset();

	for (int pass = 0; pass < 10; pass++) {
		std::cout << "pass: " << pass << std::endl;
		int cur_img = (rand() * (int)(num_images - 1) / RAND_MAX);
		trainingData.getNextInputs(input, cur_img);
		trainingData.showVectorVals("Input:", input); std::cout << std::endl;

		trainingData.getTargetOutputs(targets, cur_img);
		trainingData.showVectorVals("Target output:", targets); std::cout << std::endl;
		std::cout << "Target char:" << trainingData.getChar(cur_img) << std::endl;

		net.feedForward(input);
		output = net.getOutput();
		trainingData.showVectorVals("Output:", output); std::cout << std::endl;
		std::cout << "Output char" << trainingData.getCharFromOutputs(output) << std::endl;
		net.backPropagate(targets);
	}

	std::cin.ignore();
	return 0;
}