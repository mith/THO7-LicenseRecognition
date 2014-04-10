#include "NeuronLayer.h"

using namespace std;

NeuronLayer::NeuronLayer(unsigned int size, unsigned int connections_per_neuron, bool biasnode)
: biasnode(biasnode)
{
<<<<<<< HEAD
	for (unsigned int i = 0; i <= size; ++i) {
		weights.push_back(vector<float>(connections_per_neuron, rand() / float(RAND_MAX))); //Random weight of range - 1 to 1
		outputvalues.push_back(0.0);
=======
	for (unsigned int i = 0; i < size; ++i) {
		weights.emplace_back(connections_per_neuron, rand() / float(RAND_MAX)); //Random weight of range - 1 to 1
		delta_weights.emplace_back(connections_per_neuron, 0);
		output_values.push_back(0);
	}

	if (biasnode) {
		output_values.push_back(1);
		weights.emplace_back(connections_per_neuron, rand() / float(RAND_MAX));
		delta_weights.emplace_back(connections_per_neuron, 0);
>>>>>>> 9843492e0c0e6b942084267da7d5d30e50c7657c
	}
	outputvalues.push_back(1.0); // Set bias neuron outputvalue to 1
}


NeuronLayer::~NeuronLayer()
{
}
