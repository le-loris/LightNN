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

Network::Network(const char* filename)
{
	this->loadFile();
	this->initLayers();
	this->feedForward();
	this->printWeights();
}

Network::~Network(){
}

void Network::initNetwork(){
	srand((unsigned int)time(NULL));
	this->initLayers();
	this->randomizeWeights();
	this->feedForward();
	
}

void Network::initLayers()
{
	this->layers.clear();
	for (unsigned int i = 0; i < this->structure.vector_length(); i++) {
		vector<float> temp(this->structure.at(i));
		this->layers.push_back(temp);
	}
}

void Network::randomizeWeights(){
	this->weights.clear();
	this->biases = vector<vector<float>>();
	for (unsigned int layer = 0; layer < this->structure.vector_length() - 1; layer++) {
		this->weights.push_back(Matrix<float>(this->structure.at(layer), this->structure.at(layer+1)));
		this->biases.push_back(vector<float>());
		
		for (unsigned int neuron = 0; neuron < this->structure.at(layer+1); neuron++) {
			this->biases.back().push_back(2.f * ((float)rand() / (float)RAND_MAX) - 1.f);
		
			for (unsigned int weight = 0; weight < this->structure.at(layer); weight++) {
				this->weights.at(layer).at(weight, neuron) = 2.f*((float)rand() / (float)RAND_MAX) - 1.f;
			}
		}
	}
}

void Network::printWeights()
{
	for(unsigned int layer = 0; layer < this->structure.vector_length() - 1; layer++) {
		std::cout << "Layer " << layer+1 << std::endl;
		std::cout << this->weights.at(layer) << std::endl << std::endl;
	}
}

vector<float> Network::setTrainingData(TrainingData trainingData)
{
	for(unsigned int i = 0; i < trainingData.inp.vector_length(); i++){
		this->layers.at(0).at(i) = trainingData.inp.at(i);
	}
	return trainingData.out;
}

vector<float> Network::feedForward(){
    for(unsigned int layer = 1; layer < this->structure.vector_length(); layer++) {
		this->layers.at(layer) = this->biases.at(layer-1) + this->weights.at(layer - 1) * this->layers.at(layer - 1);
	}

	return this->layers.back();
}

vector<vector<float>> Network::backPropagation(vector<float> final_error)
{
	vector<vector<float>> layers_errors;
	vector<float> prev_error;
	layers_errors.push_back(final_error);
		
	for(unsigned int i = this->structure.vector_length(); i>1; i--){
		vector<float> error = layers_errors.back();
		prev_error = weights.at(i-2).transpose() * error;
		layers_errors.push_back(prev_error);
	}

	return layers_errors;
}

void Network::adjustWeights(vector<vector<float>> variation)
{
	for(unsigned int i = this->structure.vector_length(); i>1; i--){
		vector<float> layer_error = variation.at(this->structure.vector_length() - 1);
		vector<float> layer_value = this->layers.at(i-1);
		vector<float> prev_layer_value = this->layers.at(i-2);
		vector<float> gradient = layer_error * layer_value;
		Matrix<float> delta = (gradient & prev_layer_value) * this->learningRate;
		this->weights.at(i-2) += delta;
	}

	for(unsigned int layer = 1; layer < this->structure.vector_length(); layer++)
		for (unsigned int neuron = 0; neuron < this->structure.at(layer); neuron++) 
			for(unsigned int weight = 0; weight < this->structure.at(layer-1); weight++)
				this->weights.at(layer-1).at(neuron, weight) = MIN(MAX(this->weights.at(layer-1).at(neuron, weight), -1.f), 1.f);
}

void Network::train(){
	for(unsigned int i = 0; i < this->trainingData.vector_length(); i++){
		vector<float> exp_output = this->setTrainingData(this->trainingData.at(i));
		vector<float> act_output = this->feedForward();
		vector<float> error = exp_output - act_output;
		this->error_historic.push_back(error.norm_sq());
		vector<vector<float>> variation = this->backPropagation(error);
		this->adjustWeights(variation);
	}
}

void Network::saveFile(const char* filename) {
	FILE* F = NULL;
	F = fopen(filename, "w");
	
	if (F == NULL)
		throw "Error while opening file\n";
	int length = (this->structure.vector_length() + 1) * 5;
	char* structure = new char[length];
	sprintf(structure, "%d", this->structure.vector_length());
	for (unsigned int i = 0; i < this->structure.vector_length(); i++) {
		char* temp = new char[5];
		sprintf(temp, ", %d", this->structure.at(i));
		strcat(structure, temp);
		delete[] temp;
	}
	fprintf(F, "%s\n", structure);
	for (unsigned int i = 0; i < this->structure.vector_length() - 1; i++) {
		for(unsigned int j = 0; j < this->structure.at(i+1); j++){
			for(unsigned int k = 0; k < this->structure.at(i); k++){
				fprintf(F, "%f, ", this->weights.at(i).at(k, j));
			}
			fprintf(F, "%f, ", this->biases.at(i).at(j));
			fprintf(F, "\n");
		}
		fprintf(F, "\n");
	}	
	fclose(F);
}

void Network::loadFile(const char* filename) {
	FILE* F = NULL;
	F = fopen(filename, "r");

	if (F == NULL)
		throw "Error while opening file\n";
	
	this->structure = vector<unsigned int>();
	char *buf = new char[5];
	int bufint;
	fscanf(F, "%s", buf);
	bufint = atoi(buf);
	for(int i = 0; i < bufint; i++){
		fscanf(F, "%s", buf);
		bufint = atoi(buf);
		this->structure.push_back(bufint);
		printf("%d ", bufint);
	}

	this->weights = vector<Matrix<float>>();
	
	float buffloat;
	for (unsigned int i = 0; i < this->structure.vector_length() - 1; i++) {
		this->weights.push_back(Matrix<float>(this->structure.at(i), this->structure.at(i + 1)));
		this->biases.push_back(vector<float>());
		for (unsigned int j = 0; j < this->structure.at(i + 1); j++) {
			for (unsigned int k = 0; k < this->structure.at(i); k++) {
				fscanf(F, "%s", buf);
				buffloat = (float)atof(buf);
				this->weights.at(i).at(k, j) = buffloat;
				printf("%f ", buffloat);
			}
			fscanf(F, "%s", buf);
			buffloat = (float)atof(buf);
			this->biases.at(i).push_back(buffloat);
			printf("%f ", buffloat);
			printf("\n");
		}
		printf("\n");
	}

	fclose(F);
}
