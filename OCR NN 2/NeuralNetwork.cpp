#include "NeuralNetwork.h"
#include "basetimer.h"
#include <amp_math.h>

using namespace std;

NeuralNetwork::NeuralNetwork(const std::vector<unsigned int> topology)
{
	// Every element in the topology vector represents a layer, the value of each element is the amount of neurons in that layer
	for (const auto & lc : topology) {
		layers.emplace_back(lc, lc);
	}
}


std::vector<float> NeuralNetwork::getOutput() const
{
	return layers.back().outputvalues;
}


NeuralNetwork::~NeuralNetwork()
{
}

void NeuralNetwork::feedForward(const vector<float> &input) {
	if (layers[0].outputvalues.size() != input.size()) {
		throw new std::runtime_error("Invalid input values");
	}

	layers[0].outputvalues = input;

	for (unsigned int l_id = 0; l_id < num_layers() - 1; l_id++) {
		const NeuronLayer & layer = layers[l_id];

		NeuronLayer & next_layer = layers[l_id + 1];

		for (int n_id = 0; n_id < layer.num_nodes(); n_id++) {
			const __m256 outputvalue = _mm256_broadcast_ss(&layer.outputvalues[n_id]);

			const int md_iter = next_layer.num_nodes() / 8;

			const float * node_weights_ptr = layer.weights[n_id].data();
			float * layer_output_ptr = next_layer.outputvalues.data();

			for (int iter = 0; iter < md_iter; iter++) {
				const __m256 ws = _mm256_loadu_ps((const float *)(node_weights_ptr));

				_mm256_storeu_ps(layer_output_ptr, _mm256_mul_ps(outputvalue, ws));

				node_weights_ptr += 8;
				layer_output_ptr += 8;
			}

			const int rest = next_layer.num_nodes() % 8;

			for (int riter = 0; riter < rest; riter++) {
				*layer_output_ptr = layer.outputvalues[n_id] * (*node_weights_ptr);

				node_weights_ptr++;
				layer_output_ptr++;
			}

			for (auto & v : next_layer.outputvalues) {
				v = concurrency::precise_math::tanh(v);
				//v = tanh(v);
			}
		}
	}
}


int main() {
	std::vector<unsigned int> topology(3, 50);

	NeuralNetwork net(topology);
	std::vector<float> input(50, 1.0);

	BaseTimer tmr;
	tmr.start();
	for (int i = 0; i < 50000; i++) {
		net.feedForward(input);
	}
	tmr.stop();

	std::cout << "feedforward took: " << tmr.elapsedSeconds() << std::endl;
	return 0;


	return 0;
}
