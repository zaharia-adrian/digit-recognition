#include "NN.hpp"


NN::NN(std::vector<int> _layersSizes) {
	layersCount = _layersSizes.size();
	layersSizes = _layersSizes;

	o.emplace_back(std::vector<float>(layersSizes[0]));
	b.emplace_back();
	w.emplace_back();
	e.emplace_back();
	for (int i = 1; i < layersSizes.size(); i++) {
		b.emplace_back(std::vector<float>(layersSizes[i]));
		w.emplace_back(std::vector<std::vector<float>>(layersSizes[i], std::vector<float>(layersSizes[i - 1])));
		o.emplace_back(std::vector<float>(layersSizes[i]));
		e.emplace_back(std::vector<float>(layersSizes[i]));
	}
	//initRandom();	
	//train();
	initFromFile();
	//test();
}
void NN::initRandom() {
	std::default_random_engine generator;

	for (int layer = 1; layer < layersCount; layer++) {
		for (int i = 0; i < layersSizes[layer]; i++) {

			std::normal_distribution<float> distribution(0, sqrt(2.0f / (layersSizes[layer - 1] + layersSizes[layer])));

			for (int j = 0;j < layersSizes[layer - 1]; j++)
				w[layer][i][j] = distribution(generator);	
			b[layer][i] = 0.0f;
		}
	}
}
void NN::initFromFile() {
	FILE* fptr = fopen("../../../assets/params/params.txt", "r");
	if (fptr == NULL) {
		std::cout << "Error loading the file!";
		return;
	}
	for (int layer = 1; layer < layersCount; layer++) {
		for (int i = 0; i < layersSizes[layer]; i++) {
			for (int j = 0;j < layersSizes[layer - 1]; j++)
				fscanf(fptr, "%f", &w[layer][i][j]);
			fscanf(fptr, "%f", &b[layer][i]);
		}
	}
	fclose(fptr);
}
void NN::saveToFile() {
	FILE *fptr = fopen("../../../assets/params/params.txt", "w");
	if (fptr == NULL) {
		std::cout << "Error loading the file!";
		return;
	}
	for (int layer = 1; layer < layersCount; layer++) {
		for (int i = 0; i < layersSizes[layer]; i++) {
			for (int j = 0;j < layersSizes[layer - 1]; j++)
				fprintf(fptr, "%f ", w[layer][i][j]);
			fprintf(fptr, "%f ", b[layer][i]);
		}
	}
	fclose(fptr);
}
void NN::initInputLayer(std::vector<float> inputLayer) {
	for(int i=0;i<layersSizes[0];i++)
		o[0][i] = inputLayer[i] * 0.99 + 0.01;
}
std::vector<float> NN::query(std::vector<float> inputLayer) {
	initInputLayer(inputLayer);
	forwardProp();
	return o[layersCount - 1];
}
void NN::train() {

	///1st attempt, initial learning rate 0.1, at each step subtract 0.00001, got to -0.6 :))
	///2nd attempt, lowering hidden layer from 500 to 100, const learning rate
	///3rd attempt, back to 500 neurons in the hidden layer
	/// ...
	/// got to an accuracy of 95%

	auto images = FileManager::loadMNISTImages("../../../assets/mnist/train-images.idx3-ubyte");
	auto labels = FileManager::loadMNISTLabels("../../../assets/mnist/train-labels.idx1-ubyte");
	
	
	for (int i = 0;i < images.size();i++) {
		
		if (i % 100 == 0) std::cout << "Trained on " << i << " examples...\n";
		for (int j = 0;j < 28 * 28;j++) {
			o[0][j] = (static_cast<float>(images[i][j]) / 255) * 0.99 + 0.01;
		}
		forwardProp();
		outputError(labels[i]);
		backwardProp();
	}
	
	saveToFile();
}
void NN::test() {
	auto images = FileManager::loadMNISTImages("../../../assets/mnist/test-images.idx3-ubyte");
	auto labels = FileManager::loadMNISTLabels("../../../assets/mnist/test-labels.idx1-ubyte");

	if (images.size() != labels.size()) {
		std::cout << "Something wrong!";
		return;
	}
	int correct = 0;
	for (int i = 0;i < images.size();i++) {
		if (i % 100 == 0) std::cout << "Tested " << i << " examples...\n";
		for (int j = 0;j < 28 * 28;j++) {
			o[0][j] = (static_cast<float>(images[i][j]) / 255) * 0.99 + 0.01;
		}
		forwardProp();
		int label = -1;
		float maxim = 0;
		for (int j = 0;j <= 9;j++) {
			if (maxim < o[layersCount - 1][j]) {
				label = j; maxim = o[layersCount - 1][j];
			}
		}
		if (label == labels[i]) correct++;
	}
	std::cout << "\nTested...\n" << correct << " out of " << images.size() << "( "<<100.0f * correct / images.size()<<"% )";

}


void NN::forwardProp() {
	for (int layer = 1; layer < layersCount; layer++) {
		for (int i = 0; i < layersSizes[layer]; i++){
			o[layer][i] = 0;
			for (int j = 0; j < layersSizes[layer - 1];j++) 
				o[layer][i] += w[layer][i][j] * o[layer - 1][j];
				
			o[layer][i] += b[layer][i];
			o[layer][i] = sigmoid(o[layer][i]);
		}
	}
}
void NN::backwardProp() {
	for (int layer = layersCount - 2; layer >= 1; layer--) {
		for (int i = 0; i < layersSizes[layer]; i++) {
			e[layer][i] = 0;
			for (int j = 0; j < layersSizes[layer + 1]; j++)
				e[layer][i] += w[layer+1][j][i] * e[layer + 1][j];	
		}
	}
	for (int layer = 1; layer < layersCount; layer++) {
		for (int i = 0; i < layersSizes[layer]; i++) {
			float delta = learningRate * e[layer][i] * o[layer][i] * (1 - o[layer][i]);
			for (int j = 0; j < layersSizes[layer - 1];j++) {
				w[layer][i][j] += delta * o[layer - 1][j];	
			}
			b[layer][i] += delta;
		}
	}
}

void NN::printParams() {
	for (int layer = 0; layer < layersCount; layer++) {
		std::cout << "-------------------------------\nLayer " << std::to_string(layer)<<'\n';
		std::cout << "Weights:\n";
		for (int i = 0;i < w[layer].size();i++) {
			for (int j = 0;j < w[layer][i].size();j++) {
				std::cout << w[layer][i][j] << ' ';
			}
			std::cout << '\n';
		}

		std::cout << "Biases:\n";
		for (int i = 0;i<b[layer].size();i++) {
			std::cout << b[layer][i] << ' ';
		}
		std::cout << '\n';
	}
}
void NN::printOutputAndError() {
	for (int layer = 0; layer < layersCount; layer++) {
		std::cout << "-------------------------------\nLayer " << std::to_string(layer) << '\n';
		std::cout << "Output:\n";
		for(int i=0;i<o[layer].size();i++)
			std::cout << o[layer][i] << ' ';	
		
		std::cout << "Error:\n";
		for (int i = 0;i < e[layer].size();i++)
			std::cout << e[layer][i] << ' ';
		std::cout << '\n';
	}
}


void NN::outputError(int label) {
	for (int i = 0; i <= 9; i++) {
		e[layersCount - 1][i] = (i == label ? 0.99f : 0.01f) - o[layersCount - 1][i];
	}
}

float NN::sigmoid(float n) {
	return 1.0f / ( 1.0f + exp( -n ) );
}