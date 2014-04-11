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
	unsigned int num_nodes() const { return static_cast<unsigned int>(output_values.size()); }
	unsigned int num_mut_nodes() const { return static_cast<unsigned int>(output_values.size() - (biasnode ? 1 : 0)); }
};

