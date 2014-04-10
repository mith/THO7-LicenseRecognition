#include "NeuralNetwork.h"
#define TRAINING_RATE 0.2f
#include "basetimer.h"
#include <ppl.h>

using namespace std;

NeuralNetwork::NeuralNetwork(const std::vector<unsigned int> topology)
{
	// Every element in the topology vector represents a layer, the value of each element is the amount of neurons in that layer
	for (unsigned int layer = 0; layer < topology.size() - 1; layer++) {
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

	for (unsigned int i = 0; i < layers[0].num_nodes() - 1; i++) {
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
}

void NeuralNetwork::backPropagate(const std::vector<float> &target) {
	NeuronLayer &output_layer = layers.back();
	for (unsigned int neuron = 0; neuron < output_layer.output_values.size() - 1; ++neuron) {
		float neuron_error = target[neuron] - output_layer.output_values[neuron]; // Calculate neuron error
		//Calculate gradient for this output neuron by multiplying the neuron error with the derivative of the outputvalue of tanh
		output_layer.gradients[neuron] = neuron_error * (1 - (tanh(output_layer.output_values[neuron]) * tanh(output_layer.output_values[neuron])));
	}

	// Calculate hidden layer(s) neuron gradients
	for (unsigned int layer = static_cast<unsigned int>(layers.size() - 2); layer != 0; --layer) {
		for (unsigned int current_neuron = 0; current_neuron < layers[layer].output_values.size(); ++current_neuron) {
			float sum = 0.0; // Sum of this neuron's contribution to the errors of the next layer
			for (unsigned int next_neuron = 0; next_neuron < layers[layer + 1].output_values.size() - 1; ++next_neuron) {
				sum += layers[layer].weights[current_neuron][next_neuron] * layers[layer + 1].gradients[next_neuron];
			}
			layers[layer].gradients[current_neuron] = sum * (1 - (tanh(output_layer.output_values[current_neuron]) * tanh(output_layer.output_values[current_neuron])));
		}
	}

	// Update weights in all layers
	for (unsigned int layer = static_cast<unsigned int>(layers.size() - 1); layer != 0; --layer) {
		for (unsigned int current_neuron = 0; current_neuron < layers[layer].output_values.size() - 1; ++current_neuron) {
			for (unsigned int input_neuron = 0; current_neuron < layers[layer - 1].output_values.size(); ++input_neuron) {
				layers[layer - 1].weights[input_neuron][current_neuron] += TRAINING_RATE * layers[layer - 1].output_values[input_neuron] * layers[layer].gradients[current_neuron];
			}
		}
	}
}

vector<float>& NeuralNetwork::getOutput() {
	return layers.back().output_values;
}

int main() {
	std::vector<unsigned int> topology({ 20, 30, 36 });

	NeuralNetwork net(topology);
	std::vector<float> input(20, 0.88f);

	BaseTimer tmr;
	tmr.start();
	for (int i = 0; i < 1000000; i++) {
		net.feedForward(input);
	}
	tmr.stop();

	std::cout << "feedforward took: " << tmr.elapsedSeconds() << std::endl;
	std::cin.ignore();
	return 0;
}
