
#include "NN.hpp"










float NN::sigmoid(float n) {
	return 1.0f / ( 1.0f + exp( -n ) );
}