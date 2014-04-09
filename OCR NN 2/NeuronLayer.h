#pragma once
#include <vector>
#include <amp.h>

struct NeuronLayer
{
	NeuronLayer(int size, int connections_per_neuron);
	~NeuronLayer();

	int num_nodes() const
	{
		return values.extent.size();
	}

	concurrency::array<float, 1> values;
	concurrency::array<float, 2> weights;
	concurrency::array<float, 2> delta_weights;
	/*std::vector<float> outputvalues;

	std::vector<std::vector<float>> weights;
	std::vector<std::vector<float>> delta_weights;*/
};

