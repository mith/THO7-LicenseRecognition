#pragma once

#include "NeuronLayer.h"

#include <vector>

class NeuralNetwork
{
public:
	NeuralNetwork(const std::vector<unsigned int> topology);
	~NeuralNetwork();
	void feedForward(const std::vector<float> &input);
	void backPropagate(const std::vector<float> &target);
	std::vector<float>& getOutput();

private:
	std::vector<NeuronLayer> layers;
	float network_error;
};

