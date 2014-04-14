#include "NN_TrainingData.h"

NN_TrainingData::NN_TrainingData(const std::string filename) {
	m_trainingDataFile.open(filename.c_str());

}


NN_TrainingData::~NN_TrainingData() {
}

void NN_TrainingData::getTopology(std::vector<unsigned> &topology) {
	std::string line;
	std::string label;

	getline(m_trainingDataFile, line);
	std::stringstream ss(line);
	ss >> label;
	if(this->isEof() || label.compare("topology:") != 0) {
		abort();
	}

	while(!ss.eof()) {
		unsigned n;
		ss >> n;
		topology.push_back(n);
	}

	return;
}

unsigned NN_TrainingData::getNextInputs(std::vector<double> &inputVals) {
	inputVals.clear();

	std::string line;
	getline(m_trainingDataFile, line);
	std::stringstream ss(line);

	std::string label;
	ss >> label;
	if(label.compare("in:") == 0) {
		double oneValue;
		while(ss >> oneValue) {
			inputVals.push_back(oneValue);
		}
	}

	return inputVals.size();
}

unsigned NN_TrainingData::getTargetOutputs(std::vector<double> &targetOutputVals) {
	targetOutputVals.clear();

	std::string line;
	getline(m_trainingDataFile, line);
	std::stringstream ss(line);

	std::string label;
	ss >> label;
	if(label.compare("out:") == 0) {
		double oneValue;
		while(ss >> oneValue) {
			targetOutputVals.push_back(oneValue);
		}
	}

	return targetOutputVals.size();
}

void NN_TrainingData::showVectorVals(std::string label, std::vector<double> &v) {
	std::cout << label << " ";
	for(unsigned i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}

	std::cout << std::endl;
}
