#include "NeuronLayer.h"

using namespace std;

NeuronLayer::NeuronLayer(unsigned int size, unsigned int connections_per_neuron)
{
	for (unsigned int i = 0; i <= size; ++i) {
		weights.push_back(vector<float>(connections_per_neuron, rand() / float(RAND_MAX))); //Random weight of range - 1 to 1
		outputvalues.push_back(0.0);
	}
	outputvalues.push_back(1.0); // Set bias neuron outputvalue to 1
}


NeuronLayer::~NeuronLayer()
{
}
