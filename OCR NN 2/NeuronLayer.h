#pragma once

#include <vector>

#include "Neuron.h"

class NeuronLayer
{
friend class NeuralNetwork;
 
public:
	NeuronLayer(unsigned int size);
	~NeuronLayer();

	std::vector<float> outputvalues;

	std::vector<neuron_weights> weights;
	std::vector<neuron_weights> delta_weights;

	Neuron operator[] (int i) {
		return Neuron(
			outputvalues[i],
			weights[i],
			delta_weights[i]);
	}

	float & outputvalue(int i) {
		return outputvalues[i];
	}
};