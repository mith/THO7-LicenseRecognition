#pragma once

#include <vector>

struct NeuronConnection {
	float weight;
	float delta_weight;
};

class Neuron
{
public:
	Neuron(unsigned int num_connections);
	~Neuron();

private:
	float output;
	std::vector<NeuronConnection> connections;
};

