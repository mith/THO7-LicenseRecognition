// Base class: David Miller, http://millermattson.com/dave
// 
// Modified to split data in multiple files 
// and other changes by Kevin Bosman.

#pragma once
#include "NN.h"
#include "NN_Neuron.h"

class NN_Net {
private:
	std::vector<Layer> m_layers; // m_layers[layerNum][neuronNum]
	double m_error;
	double m_recentAverageError;
	static double m_recentAverageSmoothingFactor;
public:
	NN_Net(const std::vector<unsigned> &topology);
	NN_Net(const std::string &importFile);
	~NN_Net();
	void feedForward(const std::vector<double> &inputVals);
	void backProp(const std::vector<double> &targetVals);
	void getResults(std::vector<double> &resultVals) const;
	double getRecentAverageError(void) const { return m_recentAverageError; }

	// Export
	void exportNN(const std::string filename);
};