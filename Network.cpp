//
// Created by loris on 29/09/2023.
//

#include "Network.h"


Network::Network(){
	this->structure = NetStruct();
	this->structure.nbLayers = 4;
	this->structure.layers = new unsigned int[this->structure.nbLayers]{ 3, 6, 6, 2 };
	this->learningRate = 0.1;
}

Network::Network(NetStruct structure, float learningRate){
	this->structure = structure;
	this->learningRate = learningRate;
}

Network::~Network()
{
	delete[] this->structure.layers;
	delete trainingData;
}

vector<float> Network::feedForward()
{
    return vector<float>();
}
