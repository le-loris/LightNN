//
// Created by loris on 29/09/2023.
//

#include "Network.h"


Network::Network(){
	unsigned int *temp = new unsigned int[4]{ 3, 6, 6, 2 };
	this->structure = vector<unsigned int>(4, temp);

	this->learningRate = 0.1f;
	
	initNetwork();
}

Network::Network(vector<unsigned int> structure, vector<TrainingData> trainingData, float learningRate) {
	this->structure = structure;
	this->learningRate = learningRate;
	this->trainingData = trainingData;
	initNetwork();
}

Network::~Network(){
}

void Network::initNetwork(){
	srand(time(NULL));
	initLayers();
	initBias();
	randomizeWeights();
}

void Network::initLayers()
{
	this->layers.clear();
	vector<float> temp(this->structure.front());
	this->layers.push_back(temp);
	this->feedForward();
}

void Network::initBias()
{
	for (unsigned int layer = 0; layer < this->structure.size() - 1; layer++) {
		this->layers.at(layer).push_back(1.f);
		this->structure.at(layer)++;
	}
}

void Network::randomizeWeights(){
	this->weights.clear();
	for (unsigned int layer = 0; layer < this->structure.size() - 1; layer++) {
		this->weights.push_back(Matrix<float>(this->structure.at(layer), this->structure.at(layer+1)));
		for (unsigned int neuron = 0; neuron < this->structure.at(layer+1); neuron++) {
			for (unsigned int weight = 0; weight < this->structure.at(layer); weight++) {
				this->weights.at(layer).at(neuron, weight) = 2.f*((float)rand() / (float)RAND_MAX) - 1.f;
			}
		}
	}
}

vector<float> Network::setTrainingData(TrainingData trainingData)
{
	for(unsigned int i = 0; i < trainingData.inp.size(); i++){
		this->layers.at(0).at(i) = trainingData.inp.at(i);
	}
	return trainingData.out;
}

vector<float> Network::feedForward(){
    for(unsigned int i = 1; i < this->structure.size() - 1; i++) {
		this->layers.at(i) = this->weights.at(i) * this->layers.at(i-1);
	}

	return this->layers.back();
}

vector<vector<float>> Network::backPropagation(vector<float> final_error)
{
	vector<vector<float>> layers_errors;
	vector<float> prev_error;
	layers_errors.push_back(final_error);
		
	for(unsigned int i = this->structure.size(); i>1; i--){
		vector<float> error = layers_errors.back();
		prev_error = weights.at(i-2).transpose() * error;
		layers_errors.push_back(prev_error);
	}

	return layers_errors;
}

void Network::adjustWeights(vector<vector<float>> variation)
{
	for(unsigned int i = this->structure.size(); i>1; i--){
		vector<float> layer_error = variation.at(this->structure.size() - 1);
		vector<float> layer_value = this->layers.at(i-1);
		vector<float> prev_layer_value = this->layers.at(i-2);
		vector<float> gradient = layer_error * layer_value;
		Matrix<float> delta = (gradient & prev_layer_value) * this->learningRate;
		this->weights.at(i-2) += delta;
	}

	for(unsigned int layer = 1; layer < this->structure.size(); layer++)
		for (unsigned int neuron = 0; neuron < this->structure.at(layer); neuron++) 
			for(unsigned int weight = 0; weight < this->structure.at(layer-1); weight++)
				this->weights.at(layer-1).at(neuron, weight) = MIN(MAX(this->weights.at(layer-1).at(neuron, weight), -1.f), 1.f);
}

void Network::train(){
	for(unsigned int i = 0; i < this->trainingData.size(); i++){
		vector<float> exp_output = this->setTrainingData(this->trainingData.at(i));
		vector<float> act_output = this->feedForward();
		vector<float> error = exp_output - act_output;
		this->error_historic.push_back(error.norm_sq());
		vector<vector<float>> variation = this->backPropagation(error);
		this->adjustWeights(variation);
	}
}
