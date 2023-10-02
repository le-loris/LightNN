//
// Created by loris on 29/09/2023.
//

#ifndef LIGHTNN_NETWORK_H
#define LIGHTNN_NETWORK_H
#include "Matrix.h"

typedef struct NET_STRUCT {
    unsigned int nbLayers;
    unsigned int* layers;
} NetStruct;

typedef struct T_DATA {
    vector<float> inp;
    vector<float> out;
} TrainingData;



class Network {
private:
	vector<Matrix<float>> weights;
	vector<float> biases;
	Matrix<float> layers;
    NetStruct structure;
    float learningRate;
    TrainingData* trainingData;

public:
    Network();
    Network(NetStruct structure, float learningRate = 0.1);
    ~Network();

    vector<float> feedForward();
    vector<float> backPropagation();
    void train();
    void updateWeights();
    void updateBiases();
    void setTrainingData(TrainingData trainingData);
    
};


#endif //LIGHTNN_NETWORK_H
