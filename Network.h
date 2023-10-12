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
    vector<vector<float>> biases;
    vector<unsigned int> structure;
    float learningRate;
    vector<TrainingData> trainingData;

    vector<float> error_historic;
    
    void initNetwork();
    void initLayers();
    void randomizeWeights();
    void printWeights();
    
public:
    Network();
    Network(vector<unsigned int> structure, vector<TrainingData> trainingData, float learningRate = 0.1);
    Network(const char* filename);
    ~Network();

    vector<float> setTrainingData(TrainingData trainingData);
    vector<float> feedForward();
    vector<vector<float>> backPropagation(vector<float> final_error);
    void adjustWeights(vector<vector<float>> variation);
    void train();
    void saveFile(const char* filename = "network_data.csv");
    void loadFile(const char* filename = "network_data.csv");
};


#endif //LIGHTNN_NETWORK_H
