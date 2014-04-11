#include "TrainingsManager.h"


TrainingsManager::TrainingsManager(std::string img, std::string import) : trainingData(img), topology(trainingData.getTopology()),
									input(topology.front()), output(topology.back()), targets(topology.back()),
									num_images(trainingData.loadImageList()), net(topology)
{
	srand(std::time(NULL));
	inTraining = import.length() == 0;
	run();
}


TrainingsManager::~TrainingsManager()
{
}

void TrainingsManager::run() {
	//train
	int i = 0, passes = 1000;
	while ((double)correctAnswers / (double)passes < 0.028) {
		i++;
		runPasses(passes);
		std::cout << "Train session " << i << " had a succes rate of: " << (double)correctAnswers / (double)passes << '%' << std::endl;
	}
	//Check output
	runPasses(10, true);
}

void TrainingsManager::runPasses(int passes, bool print) {
	correctAnswers = 0;
	for (int pass = 0; pass < passes; pass++) {
		int cur_img = ((double)rand() / (double)(RAND_MAX + 1) * num_images);
		trainingData.getTargetOutputs(targets, cur_img);
		trainingData.getNextInputs(input, cur_img);
		net.feedForward(input);
		output = net.getOutput();
		if (trainingData.getCharFromOutputs(output)[0] == trainingData.imageData[cur_img]) {
			correctAnswers++;
		}
		if (print) {
			for (int i = 0; i < output.size(); i++) {
				std::cout << "Output: " << i << " " << output[i] << " ~ ";
			}
			std::cout << "Target char: " << trainingData.imageData[cur_img] << std::endl;
			std::cout << "Output char: " << trainingData.getCharFromOutputs(output) << std::endl << std::endl;
		}
	}
}