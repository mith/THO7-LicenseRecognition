#pragma once
#include <iostream>
#include "ImageLib.h"
#include "NeuronLayer.h"
#include "immintrin.h"

#include <vector>

class NeuralNetwork
{
public:
	NeuralNetwork(const std::vector<unsigned int> & topology);
	~NeuralNetwork();
	void feedForward(const std::vector<float> &input);
	//void backPropagate(const std::vector<float> &target);
	//std::vector<float> getOutput() const;

	int num_layers() const 
	{
		return layers.size();
	}

private:
	std::vector<NeuronLayer> layers;

	void feedForward_SSE(const std::vector<float> & input);
};

extern __m256 __cdecl _mm256_tanh_ps(__m256);

//extern __cdecl __m256 _mm256_tanh_ps(__m256 a);
