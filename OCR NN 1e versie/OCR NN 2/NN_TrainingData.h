#pragma once
#include "NN.h"
#include "Image.h"

// Silly class to read training data from a text file -- Replace This.
// Replace class TrainingData with whatever you need to get input data into the
// program, e.g., connect to a database, or take a stream of data from stdin, or
// from a file specified by a command line argument, etc.

class NN_TrainingData {
private:
	std::ifstream m_trainingDataFile;
public:
	NN_TrainingData(const std::string filename);
	~NN_TrainingData();

	bool isEof(void) { return m_trainingDataFile.eof(); }
	void getTopology(std::vector<unsigned> &topology);

	// Returns the number of input values read from the file:
	unsigned getNextInputs(std::vector<double> &inputVals);
	unsigned getTargetOutputs(std::vector<double> &targetOutputVals);

	void showVectorVals(std::string label, std::vector<double> &v);
};

