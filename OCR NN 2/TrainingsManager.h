#pragma once
#include <vector>
#include "NeuralNetwork.h"
#include "basetimer.h"
#include "ImageLib.h"
#include "OCRImageData.h"
#include <ctime>

class TrainingsManager
{
private:
	OCRImageData trainingData;
	std::vector<unsigned int> topology;
	std::vector<float> input;
	std::vector<float> output;
	std::vector<float> targets;
	int num_images;
	NeuralNetwork net;
	int correctAnswers;
	bool inTraining;
	void run();
	void runPasses(int passes, bool print = false);
public:
	TrainingsManager(std::string img, std::string import);
	~TrainingsManager();
};

