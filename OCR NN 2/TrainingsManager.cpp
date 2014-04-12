#include "TrainingsManager.h"


TrainingsManager::TrainingsManager(std::string img_dir) : trainData(img_dir), topology(trainData.getTopology()), netOCR(topology)
{
	run();
}

TrainingsManager::TrainingsManager(std::string img_dir, std::string import) : trainData(img_dir), topology(trainData.getTopology()), netOCR(topology, import), isTrained(true)
{
	run();
}

void TrainingsManager::run() {
	unsigned int passes = 1000;
	double succes = 0;
	unsigned int i = 0;
	std::cout << "One session consists off: " << passes << " iterations" << std::endl;
	//train
	if (!isTrained) {
		std::cout << "Starting the training" << std::endl;
		while (true) {
			i++;
			runOCRPasses(passes);
			succes = (double)correctAnswers / (double)passes;
			std::cout << "Session " << i << " had a succesrate of: " << succes << '%' << std::endl;
			if (succes > 0.9) break;
		}
	}

	//show off
	std::cout << "Running additional run to show off the results" << std::endl;
	runOCRPasses(10, true);
}

void TrainingsManager::runOCRPasses(unsigned int passes, bool print) {
	correctAnswers = 0;
	for (unsigned int pass = 0; pass < passes; pass++) {
		unsigned int id = (rand() * (int)(trainData.numImages() - 1) / RAND_MAX);

		auto input = trainData.img_to_input(trainData[id].image);

		netOCR.feedForward(input);

		auto results = netOCR.getOutput();
		auto targets = trainData.char_to_output(trainData[id].getChar());

		unsigned int highestR = 0;
		unsigned int highestT = 0;

		for (unsigned int i = 1; i < results.size(); i++) {
			if (results[i] > results[highestR]) highestR = i;
			if (targets[i] > targets[highestT]) highestT = i;
		}

		if (highestR == highestT) correctAnswers++;

		netOCR.backPropagate(targets);

		if (print) {
			char out = highestR < 10 ? '0' + highestR : 'A' + (highestR - 10);
			std::cout << "target char: " << trainData[id].getChar() << "   id: " << highestT << std::endl;
			std::cout << "output char: " << out << "   id: " << highestR << std::endl;
			std::cout << "results: ";
			for (int i = 0; i < results.size(); i++) {
				std::cout << " " << results[i];
			}
			std::cout << std::endl <<"targets: ";
			for (int i = 0; i < results.size(); i++) {
				std::cout << " " << targets[i];
			}
			std::cout << "------------------------" << std::endl;
		}
	}
}

TrainingsManager::~TrainingsManager()
{
}
