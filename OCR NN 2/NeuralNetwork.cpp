#include "NeuralNetwork.h"

using namespace std;

NeuralNetwork::NeuralNetwork(const std::vector<unsigned int> topology)
{
	// Every element in the topology vector represents a layer, the value of each element is the amount of neurons in that layer
	for (vector<unsigned int>::const_iterator it_layersize = topology.begin(); it_layersize != topology.end(); ++it_layersize) {
		// Since this is a fully connected neural network, every neuron needs a connection with all neurons in the next layer,
		// except for the last (output) layer
		unsigned int connections_per_neuron;
		if (it_layersize != topology.end()) {
			connections_per_neuron = *(++it_layersize);
		}
		else {
			connections_per_neuron = 0;
		}
		// Create a new layer
		layers.push_back(NeuronLayer((*it_layersize) + 1, connections_per_neuron)); // + 1 for the bias Neuron
	}
}


NeuralNetwork::~NeuralNetwork()
{
}

int main() {
	return 0;
}
