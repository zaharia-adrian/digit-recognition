#pragma once 

#include <vector>
#include <cmath>


class NN {
	
	std::vector<float> input, output;
	std::vector<std::vector<float>> hidden;


	const int inputSize = 28 * 28;
	const int hiddenSize = 50;
	const int outputSize = 10;

	float sigmoid(float);
	
public:


};