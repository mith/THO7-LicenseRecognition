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

void NeuralNetwork::feedForward(const vector<float> &input) {
#ifdef SIMD
	feedForward_SSE(input);
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

void NeuralNetwork::feedForward_SSE(const vector<float> & input)
{
	using namespace concurrency;

	for (unsigned int layer_i = 0; layer_i < num_layers() - 1; layer_i++) {
		const NeuronLayer & layer = layers[layer_i];
		NeuronLayer & next_layer = layers[layer_i + 1];

		array<const float, 1> cur_layer_values(layer.num_nodes(), layer.outputvalues);
		//array_view<const float, 2> cur_layer_weight(layer.num_nodes() * next_layer.num_nodes(), layer.weights);
		array<float, 1> next_layer_values(next_layer.num_nodes(), next_layer.outputvalues);

		int num_nodes = layer.num_nodes();

		parallel_for_each(next_layer_values.extent, [=](index<1> ind) restrict(amp) {
			float sum = 0.0;

			for (int ni = 0; ni < num_nodes; ni++) {
				sum += cur_layer_values[index<1>(ni)];// * cur_layer_weight[index<2>(ind[0], ni)];
			}

			next_layer_values[ind] = precise_math::tanh(sum);
		});
	}
	
}

//void NeuralNetwork::feedForward_SSE(const vector<float, aligned_allocator<__m256, 32>> & input)
//{
//	if (layers[0].outputvalues.size() != input.size()) {
//		throw new std::runtime_error("Invalid input values");
//	}
//
//	layers[0].outputvalues = input;
//
//	for (unsigned int l_id = 0; l_id < num_layers() - 1; l_id++) {
//		const NeuronLayer & layer = layers[l_id];
//
//		NeuronLayer & next_layer = layers[l_id + 1];
//
//		for (int n_id = 0; n_id < layer.num_nodes(); n_id++) {
//			const __m256 outputvalue = _mm256_broadcast_ss(&layer.outputvalues[n_id]);
//
//			const int md_iter = next_layer.num_nodes() / 8;
//
//			const float * node_weights_ptr = layer.weights[n_id].data();
//			float * layer_output_ptr = next_layer.outputvalues.data();
//
//			for (int iter = 0; iter < md_iter; iter++) {
//				const __m256 ws = _mm256_load_ps((const float *)(node_weights_ptr));
//
//				_mm256_store_ps(layer_output_ptr, _mm256_mul_ps(outputvalue, ws));
//
//				node_weights_ptr += 8;
//				layer_output_ptr += 8;
//			}
//
//			const int rest = next_layer.num_nodes() % 8;
//
//			for (int riter = 0; riter < rest; riter++) {
//				*layer_output_ptr = layer.outputvalues[n_id] * (*node_weights_ptr);
//
//				node_weights_ptr++;
//				layer_output_ptr++;
//			}
//
//			for (auto & v : next_layer.outputvalues) {
//				v = tanh(v);
//			}
//		}
//
//	}
//}


int main() {
	std::vector<unsigned int> topology(3, 50);

	NeuralNetwork net(topology);
	std::vector<float> input(50, 1.0);

	BaseTimer tmr;
	tmr.start();
	net.feedForward(input);
	tmr.stop();

	std::cout << "feedforward took: " << tmr.elapsedMicroSeconds() << std::endl;
	return 0;
}
