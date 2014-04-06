#pragma once

#include <vector>

#include "Neuron.h"

class NeuronLayer
{
friend class NeuralNetwork;
 
public:
	NeuronLayer(unsigned int size, unsigned int connections_per_neuron);
	~NeuronLayer();
private:
	std::vector<Neuron> neurons;
};

