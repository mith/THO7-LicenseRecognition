#pragma once

#include <vector>


struct NeuronLayer
{
friend class NeuralNetwork;
 
public:
	NeuronLayer(unsigned int size, unsigned int connections_per_neuron, bool biasnode = false);
	~NeuronLayer();

	const bool biasnode;
	std::vector<float> output_values;
	std::vector<float> gradients;
	std::vector<std::vector<float>> weights;

private:
	std::vector<std::vector<float>> delta_weights;

	int num_nodes() const { return output_values.size(); }
	int num_mut_nodes() const { return output_values.size() - (biasnode ? 1 : 0); }
};

