#pragma once
#include "NeuralNetwork.h"
#include "TrainData.h"

class TrainingsManager
{
private:
	TrainData trainData;
	std::vector<unsigned int> topology;
	NeuralNetwork netOCR;
	bool isTrained = false;
	void run();
	unsigned int correctAnswers;
	void runOCRPasses(unsigned int passes, bool print = false);
public:
	TrainingsManager(std::string img_dir);
	TrainingsManager(std::string img_dir, std::string import);
	~TrainingsManager();
};

