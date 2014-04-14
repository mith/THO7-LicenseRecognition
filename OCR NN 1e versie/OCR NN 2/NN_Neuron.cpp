#include "NN_Neuron.h"

// NN_Neuron constants
double NN_Neuron::eta = 0.15;    // overall net learning rate, [0.0..1.0]
double NN_Neuron::alpha = 0.05;   // momentum, multiplier of last deltaWeight, [0.0..1.0]

NN_Neuron::NN_Neuron(unsigned numOutputs, unsigned myIndex) {
	for(unsigned c = 0; c < numOutputs; ++c) {
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = randomWeight();
	}

	m_myIndex = myIndex;
}

NN_Neuron::~NN_Neuron() {
}

void NN_Neuron::feedForward(const Layer &prevLayer) {
	double sum = 0.0;

	// Sum the previous layer's outputs (which are our inputs)
	// Include the bias node from the previous layer.

	for(unsigned n = 0; n < prevLayer.size(); ++n) {
		sum += prevLayer[n].getOutputVal() *
			prevLayer[n].m_outputWeights[m_myIndex].weight;
	}

	m_outputVal = NN_Neuron::transferFunction(sum);
}

double NN_Neuron::transferFunctionDerivative(double x) {
	// tanh derivative
	return 1.0 - x * x;
}

double NN_Neuron::transferFunction(double x) {
	// tanh - output range [-1.0..1.0]

	return tanh(x);
}

void NN_Neuron::calcOutputGradients(double targetVal) {
	double delta = targetVal - m_outputVal;
	m_gradient = delta * NN_Neuron::transferFunctionDerivative(m_outputVal);
}

void NN_Neuron::calcHiddenGradients(const Layer &nextLayer) {
	double dow = sumDOW(nextLayer);
	m_gradient = dow * NN_Neuron::transferFunctionDerivative(m_outputVal);
}

double NN_Neuron::sumDOW(const Layer &nextLayer) const {
	double sum = 0.0;

	// Sum our contributions of the errors at the nodes we feed.

	for(unsigned n = 0; n < nextLayer.size() - 1; ++n) {
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}

void NN_Neuron::updateInputWeights(Layer &prevLayer) {
	// The weights to be updated are in the Connection container
	// in the neurons in the preceding layer

	for(unsigned n = 0; n < prevLayer.size(); ++n) {
		NN_Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

		double newDeltaWeight =
			// Individual input, magnified by the gradient and train rate:
			eta
			* neuron.getOutputVal()
			* m_gradient
			// Also add momentum = a fraction of the previous delta weight;
			+ alpha
			* oldDeltaWeight;

		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}