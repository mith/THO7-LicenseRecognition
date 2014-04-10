#pragma once

#include <vector>


struct NeuronLayer
{
friend class NeuralNetwork;
 
public:
	NeuronLayer(unsigned int size, unsigned int connections_per_neuron, bool biasnode = false);
	~NeuronLayer();
<<<<<<< HEAD
=======

	const bool biasnode;
	std::vector<float> output_values;
>>>>>>> 9843492e0c0e6b942084267da7d5d30e50c7657c

	std::vector<float> outputvalues;
	std::vector<float> gradients;
	std::vector<std::vector<float>> weights;
<<<<<<< HEAD
private:
=======
	std::vector<std::vector<float>> delta_weights;

	int num_nodes() const { return output_values.size(); }
	int num_mut_nodes() const { return output_values.size() - (biasnode ? 1 : 0); }
>>>>>>> 9843492e0c0e6b942084267da7d5d30e50c7657c
};

