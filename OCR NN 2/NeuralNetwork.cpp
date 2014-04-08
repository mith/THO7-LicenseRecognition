#include "NeuralNetwork.h"

using namespace std;

NeuralNetwork::NeuralNetwork(const std::vector<unsigned int> topology)
{
	// Every element in the topology vector represents a layer, the value of each element is the amount of neurons in that layer
	for (auto layersize : topology) {
		layers.emplace_back(layersize);
	}
}

void NeuralNetwork::feedForward(const std::vector<float> & input)
{
	for (int i = 0; i < layers.size(); i++) {

	}
}

std::vector<float> NeuralNetwork::getOutput() const
{
	return layers.back().outputvalues;
}


NeuralNetwork::~NeuralNetwork()
{
}

int main() {
	return 0;
}
