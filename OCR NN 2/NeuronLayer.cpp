#include "NeuronLayer.h"

using namespace std;

NeuronLayer::NeuronLayer(unsigned int size, unsigned int connections_per_neuron)
{
	for (unsigned int i = 0; i < size; ++i) {
		weights.push_back(vector<float>(connections_per_neuron, rand() / float(RAND_MAX))); //Random weight of range - 1 to 1
		delta_weights.push_back(vector<float>(connections_per_neuron, 0));
		outputvalues.push_back(0);
	}
}


NeuronLayer::~NeuronLayer()
{
}
