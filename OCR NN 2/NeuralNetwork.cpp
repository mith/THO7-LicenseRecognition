#include "NeuralNetwork.h"
#include "basetimer.h"
#include <amp.h>
#include <amp_math.h>
#include <iostream>

using namespace std;

NeuralNetwork::NeuralNetwork(const std::vector<unsigned int> & topology)
{
	//// Every element in the topology vector represents a layer, the value of each element is the amount of neurons in that layer
	//for (vector<unsigned int>::const_iterator it_layersize = topology.begin(); it_layersize != topology.end(); ++it_layersize) {
	//	// Since this is a fully connected neural network, every neuron needs a connection with all neurons in the next layer,
	//	// except for the last (output) layer
	//	unsigned int connections_per_neuron;
	//	if (it_layersize != topology.end()) {
	//		connections_per_neuron = *(++it_layersize);
	//	}
	//	else {
	//		connections_per_neuron = 0;
	//	}
	//	// Create a new layer
	//	layers.push_back(NeuronLayer((*it_layersize) + 1, connections_per_neuron)); // + 1 for the bias Neuron
	//}

	for (const auto & lc : topology) {
		layers.emplace_back(lc, lc);
	}
}




NeuralNetwork::~NeuralNetwork()
{
}

void NeuralNetwork::feedForward(const vector<float> &input) 
{
	if (input.size() != layers[0].num_nodes()) {
		throw new std::runtime_error("Wrong size input vector");
	}

#ifdef SIMD
	feedForward_AMP(input);
#endif

#ifndef SIMD
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
#endif
}


void NeuralNetwork::feedForward_AMP(const vector<float> & input)
{
	using namespace concurrency;

	array_view<const float, 1> input_view(input.size(), input);

	//input_view.copy_to(layers[0].values);

	for (int layer_i = 0; layer_i < num_layers() - 1; layer_i++) {
		const NeuronLayer & layer = layers[layer_i];
		NeuronLayer & next_layer = layers[layer_i + 1];
		int num_nodes = layer.num_nodes();

		array_view<const float, 1> cur_layer_vals(layer.values);
		array_view<float, 1> next_layer_vals(next_layer.values);
		array_view<const float, 2> weights(layer.weights);

		parallel_for_each(next_layer_vals.extent, [=](index<1> idx) restrict(amp) {
			float sum = 0.0;

			for (unsigned int nr = 0; nr < num_nodes; nr++) {
				sum += cur_layer_vals[index<1>(nr)] * weights[index<2>(idx[0], nr)];
			}

			next_layer_vals[idx];
		});
	}
}


int main() {
	std::vector<unsigned int> topology(3, 50);

	NeuralNetwork net(topology);
	std::vector<float> input(50, 1.0);

	BaseTimer tmr;
	tmr.start();
	for (int i = 0; i < 100000; i++) {
		net.feedForward(input);
	}
	tmr.stop();

	std::cout << "feedforward took: " << tmr.elapsedSeconds() << std::endl;
	return 0;
}
