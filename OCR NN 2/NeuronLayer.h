#pragma once

#include <vector>


struct NeuronLayer
{
friend class NeuralNetwork;
 
public:
	NeuronLayer(unsigned int size, unsigned int connections_per_neuron);
	~NeuronLayer();
	std::vector<float> outputvalues;

	std::vector<std::vector<float>> weights;
	std::vector<std::vector<float>> delta_weights;

	int num_nodes() const { return outputvalues.size(); }
};

