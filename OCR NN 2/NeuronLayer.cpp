#include "NeuronLayer.h"

NeuronLayer::NeuronLayer(int size, int connections_per_neuron)
: values(size), weights(size, connections_per_neuron), delta_weights(size, connections_per_neuron)
{
	using namespace concurrency;
	for (int n = 0; n < size; n++) {
		std::vector<float> tmp_weights;
		for (int w = 0; w < connections_per_neuron; w++) {
			tmp_weights.emplace_back(rand() / float(RAND_MAX));
		}

		array_view<const float, 1> tmp_weights_view(tmp_weights);
		array_view<float, 2> weights(weights);

		concurrency::parallel_for_each(concurrency::extent<1>(connections_per_neuron), [=](index<1> idx) restrict (amp) {
			weights[index<2>(n, idx[0])] = tmp_weights_view[idx];
		});
	}
}


NeuronLayer::~NeuronLayer()
{
}
