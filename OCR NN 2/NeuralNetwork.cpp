#include "NeuralNetwork.h"
#include "basetimer.h"
#include <ppl.h>

using namespace std;

NeuralNetwork::NeuralNetwork(const std::vector<unsigned int> topology)
{
	// Every element in the topology vector represents a layer, the value of each element is the amount of neurons in that layer
	for (int layer = 0; layer < topology.size() - 1; layer++) {
		layers.emplace_back(topology[layer], topology[layer + 1], true);
	}

	layers.emplace_back(topology.back(), 0);
}




NeuralNetwork::~NeuralNetwork()
{
}

void NeuralNetwork::feedForward(const vector<float> &input) {
	// Set input values of input neurons
	if (input.size() != layers[0].num_nodes() - 1) {
		throw new std::runtime_error("Wrong size input vector");
	}

	for (int i = 0; i < layers[0].num_nodes() - 1; i++) {
		layers[0].output_values[i] = input[i];
	}

	// loop through layers after input layer
	for (unsigned int layer_i = 1; layer_i < num_layers(); ++layer_i) {
		// loop through every neuron of current layer except bias neuron
		NeuronLayer & current_layer = layers[layer_i];

		for (unsigned int current_neuron = 0; current_neuron < current_layer.num_mut_nodes(); ++current_neuron) {
			// Sum all the connections to this neuron from the previous layer
			float sum = 0.0;
			const NeuronLayer & previous_layer = layers[layer_i - 1];
			// Loop through all connections from the previous layer to this neuron	
			for (unsigned int input_neuron = 0; input_neuron < previous_layer.num_nodes(); ++input_neuron) {
				sum += previous_layer.output_values[input_neuron] * previous_layer.weights[input_neuron][current_neuron];
			}
			current_layer.output_values[current_neuron] = tanh(sum);
		};
	}
	//
}


int main() {
	std::vector<unsigned int> topology({ 20, 30, 36 });

	NeuralNetwork net(topology);
	std::vector<float> input(20, 0.88);

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
