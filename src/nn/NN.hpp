#pragma once 

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <string>
#include "../../src/managers/FileManager.hpp"

class NN {
	
	int layersCount;
	std::vector<int> layersSizes;
	///will implement later for multiple training examples
	std::vector<std::vector<float>> b, o, e;
	std::vector<std::vector<std::vector<float>>> w;
	
	float learningRate = 0.1f;


	float sigmoid(float);
	void outputError(int idx);
	void initRandom(); 

	void forwardProp();
	void backwardProp();

public:
	NN(std::vector<int>);

	void initFromFile();
	void saveToFile();

	void train();
	void initInputLayer(std::vector<float>);
	std::vector<float> query(std::vector<float>);
	void print();

};