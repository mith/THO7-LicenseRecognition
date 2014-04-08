#pragma once

#include <vector>

typedef std::vector<float> neuron_weights;

struct Neuron {
	float & outputvalue;
	neuron_weights & weights;
	neuron_weights & delta_weights;

	Neuron(float & ov, neuron_weights & ws, neuron_weights & dws)
		: outputvalue(ov), weights(ws), delta_weights(dws) {}
};

