#include "NeuronLayer.h"

using namespace std;

NeuronLayer::NeuronLayer(int size, int connections_per_neuron)
: values(size), weights(size, connections_per_neuron), delta_weights(size, connections_per_neuron)
{
	for (int n = 0; n < size; n++) {
		values[concurrency::index<1>(n)] = 0;
		for (int w = 0; w < connections_per_neuron; w++) {
			concurrency::index<2> idx(n, w);
			weights[idx] = rand() / float(RAND_MAX);
			delta_weights[idx] = 0;
		}
	}
}


NeuronLayer::~NeuronLayer()
{
}
