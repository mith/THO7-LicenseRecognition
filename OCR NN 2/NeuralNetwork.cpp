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

void NeuralNetwork::feedForward(const vector<float> &input) {
	// Set input values of input neurons
	for (unsigned int i = 0; (i < input.size()) && (i < layers[0].outputvalues.size()); ++i) {
		layers[0].outputvalues[i] = input[i];
	}

	// loop through layers after input layer
	for (unsigned int current_layer = 1; current_layer < layers.size(); ++current_layer) {
		// loop through every neuron of current layer except bias neuron
		for (unsigned int current_neuron = 0; current_neuron < layers[current_layer].outputvalues.size() - 1; ++current_neuron) {
			// Sum all the connections to this neuron from the previous layer
			float sum = 0.0;
			NeuronLayer &previous_layer = layers[current_layer - 1];
			// Loop through all connections from the previous layer to this neuron	
			for (unsigned int input_neuron = 0; input_neuron < previous_layer.outputvalues.size(); ++input_neuron) {
				sum += previous_layer.outputvalues[input_neuron] * previous_layer.weights[input_neuron][current_neuron];
			}
			layers[current_layer].outputvalues[current_neuron] = tanh(sum);
		}
	}
	//
}


int main() {
	return 0;
}
