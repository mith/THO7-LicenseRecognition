#pragma once

// neural-net-tutorial.cpp
// David Miller, http://millermattson.com/dave
// See the associated video for instructions: http://vimeo.com/19569529
// 
// Base class from internet and modified to split data in multiple files 
// and other changes by Kevin Bosman.

// Global includes for the Neural Network
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>

class NN_Neuron;

// Atributes of a connection
struct Connection {
	double weight;
	double deltaWeight;
};

// Typedef of a Layer
typedef std::vector<NN_Neuron> Layer;
