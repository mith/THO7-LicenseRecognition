#include "NeuralNetwork.h"
#include "basetimer.h"

using namespace std;

NeuralNetwork::NeuralNetwork(const std::vector<unsigned int> topology)
{
	// Every element in the topology vector represents a layer, the value of each element is the amount of neurons in that layer
	for (const auto & lc : topology) {
		layers.emplace_back(lc + 1, lc + 1);
	}
}




NeuralNetwork::~NeuralNetwork()
{
}

void NeuralNetwork::feedForward(const vector<float> &input) {
	// Set input values of input neurons
	if (input.size() != layers[0].num_nodes()) {
		throw new std::runtime_error("Wrong size input vector");
	}

	layers[0].outputvalues = input;

	// loop through layers after input layer
	for (unsigned int current_layer = 1; current_layer < num_layers(); ++current_layer) {
		// loop through every neuron of current layer except bias neuron

		for (unsigned int current_neuron = 0; current_neuron < layers[current_layer].num_nodes() - 1; ++current_neuron) {
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
	std::vector<unsigned int> topology(3, 50);

	NeuralNetwork net(topology);
	std::vector<float> input(50, 1.0);

	BaseTimer tmr;
	tmr.start();
	for (int i = 0; i < 1000000; i++) {
		net.feedForward(input);
	}
	tmr.stop();

	std::cout << "feedforward took: " << tmr.elapsedSeconds() << std::endl;
	return 0;


	return 0;
}
