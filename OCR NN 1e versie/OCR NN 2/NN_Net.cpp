#include "NN_Net.h"

// NN_Net constants
double NN_Net::m_recentAverageSmoothingFactor = 100.0; // Number of training samples to average over

// Constructor with topology
NN_Net::NN_Net(const std::vector<unsigned> &topology) {
	unsigned numLayers = topology.size();
	for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
		m_layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		// We have a new layer, now fill it with neurons, and
		// add a bias neuron in each layer.
		for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
			m_layers.back().push_back(NN_Neuron(numOutputs, neuronNum));
			//std::cout << "Made a Neuron!" << std::endl;
		}

		// Force the bias node's output to 1.0 (it was the last neuron pushed in this layer):
		m_layers.back().back().setOutputVal(1.0);
	}
}

// Constructor with import file
NN_Net::NN_Net(const std::string &importFile) {
	std::ifstream importDataFile;
	importDataFile.open(importFile.c_str());
	std::string line;
	std::string label;

	// Read topology
	std::vector<unsigned> topology;

	getline(importDataFile, line);
	std::stringstream ss(line);
	ss >> label;
	if(importDataFile.eof() || label.compare("topology:") != 0) {
		abort();
	}

	while(!ss.eof()) {
		unsigned n;
		ss >> n;
		topology.push_back(n);
	}

	// Create Net
	unsigned numLayers = topology.size();
	for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
		m_layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		// We have a new layer, now fill it with neurons, and
		// add a bias neuron in each layer.
		for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
			m_layers.back().push_back(NN_Neuron(numOutputs, neuronNum));
			//std::cout << "Made a Neuron!" << std::endl;
		}

		// Force the bias node's output to 1.0 (it was the last neuron pushed in this layer):
		m_layers.back().back().setOutputVal(1.0);
	}

	// Set weights
	while(getline(importDataFile, line)) {
		// Read line
		//std::cout << line << std::endl;
		std::stringstream ss(line);

		// Read layer and neuron number
		unsigned layerNumber, neuronNumber;
		ss >> label;
		ss >> layerNumber;
		ss >> label;
		ss >> neuronNumber;

		// Get weight values
		std::vector<Connection> currentNeuronConnections;
		double weight;
		while(ss >> weight) {

			// Set connection data
			Connection connection;
			connection.weight = weight;
			currentNeuronConnections.push_back(connection);
		}

		// Push connection
		m_layers[layerNumber][neuronNumber].setWeights(currentNeuronConnections);

	}


	/*
	// Layer loop
	for(unsigned l = 0; l < topology.size() - 1; l++) {
		// Neuron loop
		for(unsigned n = 0; n < topology[l] - 1; n++) {
			getline(importDataFile, line);
			std::stringstream ss(line);
			ss >> label;

			// Check for correct layer
			if(label.compare("layer:") == 0) {
				double layerValue;
				ss >> layerValue;
				if(layerValue == l) {
					ss >> label;

					// Check for correct neuron
					if(label.compare("neuron:") == 0) {
						double neuronValue;
						ss >> neuronValue;
						if(neuronValue == n) {
							std::vector<Connection> currentNeuronConnections;

							// Read weight values
							double weight, deltaWeight;
							while(ss >> weight) {

								// Set connection data
								Connection connection;
								connection.weight = weight;
								currentNeuronConnections.push_back(connection);
							}

							// Push connection
							m_layers[l][n].setWeights(currentNeuronConnections);
						}
					}
				}
			}
		}
	}
	*/

}

NN_Net::~NN_Net() {
}

void NN_Net::getResults(std::vector<double> &resultVals) const {
	resultVals.clear();

	for(unsigned n = 0; n < m_layers.back().size() - 1; ++n) {
		resultVals.push_back(m_layers.back()[n].getOutputVal());
	}
}

void NN_Net::backProp(const std::vector<double> &targetVals) {
	// Calculate overall net error (RMS of output neuron errors)

	Layer &outputLayer = m_layers.back();
	m_error = 0.0;

	for(unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		double delta = targetVals[n] - outputLayer[n].getOutputVal();
		m_error += delta * delta;
	}
	m_error /= outputLayer.size() - 1; // get average error squared
	m_error = sqrt(m_error); // RMS

	// Implement a recent average measurement

	m_recentAverageError =
		(m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
		/ (m_recentAverageSmoothingFactor + 1.0);

	// Calculate output layer gradients

	for(unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		outputLayer[n].calcOutputGradients(targetVals[n]);
	}

	// Calculate hidden layer gradients

	for(unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum) {
		Layer &hiddenLayer = m_layers[layerNum];
		Layer &nextLayer = m_layers[layerNum + 1];

		for(unsigned n = 0; n < hiddenLayer.size(); ++n) {
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}

	// For all layers from outputs to first hidden layer,
	// update connection weights

	for(unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum) {
		Layer &layer = m_layers[layerNum];
		Layer &prevLayer = m_layers[layerNum - 1];

		for(unsigned n = 0; n < layer.size() - 1; ++n) {
			layer[n].updateInputWeights(prevLayer);
		}
	}
}

void NN_Net::feedForward(const std::vector<double> &inputVals) {
	assert(inputVals.size() == m_layers[0].size() - 1);

	// Assign (latch) the input values into the input neurons
	for(unsigned i = 0; i < inputVals.size(); ++i) {
		m_layers[0][i].setOutputVal(inputVals[i]);
	}

	// forward propagate
	for(unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {
		Layer &prevLayer = m_layers[layerNum - 1];
		for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n) {
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}
}

// Export
void NN_Net::exportNN(const std::string filename) {
	std::ofstream exportDataFile;
	exportDataFile.open(filename.c_str());

	// Topology
	exportDataFile << "topology:";
	for(unsigned l = 0; l < m_layers.size(); l++) {
		exportDataFile << " " << m_layers[l].size() - 1;
	}
	exportDataFile << std::endl;

	// Weights
	Layer currentLayer;
	// Layer loop
	for(unsigned l = 0; l < m_layers.size() - 1; l++) {
		//exportDataFile << "layer:" << l << std::endl;
		currentLayer = m_layers[l];
		// Neuron in layer loop
		for(unsigned n = 0; n < m_layers[l].size(); n++) {
			exportDataFile << "layer: " << l << " " << "neuron: " << n;
			std::vector<Connection> currentNeuronConnections;
			currentNeuronConnections = currentLayer[n].getWeights();
			// Weights loop
			for(unsigned c = 0; c < currentNeuronConnections.size(); c++) {
				exportDataFile << " " << currentNeuronConnections[c].weight;
			}
			exportDataFile << std::endl;
		}
	}
}