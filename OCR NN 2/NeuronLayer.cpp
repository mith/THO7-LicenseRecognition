#include "NeuronLayer.h"

using namespace std;

NeuronLayer::NeuronLayer(unsigned int size, unsigned int connections_per_neuron)
{
	for (unsigned int i = 0; i < size; ++i) {
		neurons.push_back(Neuron(connections_per_neuron));
	}
}


NeuronLayer::~NeuronLayer()
{
}
