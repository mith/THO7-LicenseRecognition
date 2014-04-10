#pragma once
#include <iostream>
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

	unsigned int num_layers() const { return static_cast<unsigned int>(layers.size()); }

private:
	std::vector<NeuronLayer> layers;
	float network_error;
};

