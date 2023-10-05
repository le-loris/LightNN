//
// Created by loris on 29/09/2023.
//

#ifndef LIGHTNN_NETWORK_H
#define LIGHTNN_NETWORK_H
#include "Matrix.h"

typedef struct T_DATA {
    vector<float> inp;
    vector<float> out;
} TrainingData;



class Network {
private:
	vector<Matrix<float>> weights;
    vector<vector<float>> layers;
    vector<unsigned int> structure;
    float learningRate;
    vector<TrainingData> trainingData;

    vector<float> error_historic;

public:
    Network();
    Network(vector<unsigned int> structure, vector<TrainingData> trainingData, float learningRate = 0.1);
    ~Network();

    
    void initNetwork();
    void initLayers();
    void initBias();
    void randomizeWeights();
    vector<float> setTrainingData(TrainingData trainingData);
    vector<float> feedForward();
    vector<vector<float>> backPropagation(vector<float> final_error);
    void adjustWeights(vector<vector<float>> variation);
    void train();
    
};


#endif //LIGHTNN_NETWORK_H
