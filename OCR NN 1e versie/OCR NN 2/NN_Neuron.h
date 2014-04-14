// Base class: David Miller, http://millermattson.com/dave
// 
// Modified to split data in multiple files 
// and other changes by Kevin Bosman.

#pragma once
#include "NN.h"

class NN_Neuron {
private:
	static double eta;   // [0.0..1.0] overall net training rate
	static double alpha; // [0.0..n] multiplier of last weight change (momentum)
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	static double randomWeight(void) { return rand() / double(RAND_MAX); }
	double sumDOW(const Layer &nextLayer) const;
	double m_outputVal;
	std::vector<Connection> m_outputWeights;
	unsigned m_myIndex;
	double m_gradient;
public:
	NN_Neuron(unsigned numOutputs, unsigned myIndex);
	~NN_Neuron();
	void setOutputVal(double val) { m_outputVal = val; }
	double getOutputVal(void) const { return m_outputVal; }
	void feedForward(const Layer &prevLayer);
	void calcOutputGradients(double targetVal);
	void calcHiddenGradients(const Layer &nextLayer);
	void updateInputWeights(Layer &prevLayer);

	inline std::vector<Connection> getWeights() { return m_outputWeights; };
	inline void setWeights(std::vector<Connection> &c) { m_outputWeights = c; };
};
