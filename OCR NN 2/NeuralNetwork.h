#pragma once
#include <iostream>
#include "NeuronLayer.h"

#include <vector>

class NeuralNetwork
{
public:
	NeuralNetwork(const std::vector<unsigned int> topology);
	NeuralNetwork(const std::string &importFile);
	~NeuralNetwork();
	// Feed input values through the net
	void feedForward(const std::vector<double> &input);
	// Adjust weights of the net to get closer to desired target output values
	void backPropagate(const std::vector<double> &target);
	const std::vector<double>& getOutput() const;
	// Export the net's topology and weights to a txt file
	void exportNetwork(const std::string filename) const;
	// Return the number of layers in this net
	unsigned int num_layers() const { return static_cast<unsigned int>(layers.size()); }

private:
	std::vector<NeuronLayer> layers;
	double network_error;
};

