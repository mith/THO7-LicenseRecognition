#include "Neuron.h"
#include <cstdlib>

Neuron::Neuron(unsigned int num_connections)
{
	for (unsigned int i = 0; i < num_connections; ++i) {
		connections.push_back(NeuronConnection());
		connections.back().weight = rand() / float(RAND_MAX); // Random weight of range -1 to 1
	}
}


Neuron::~Neuron()
{
}
