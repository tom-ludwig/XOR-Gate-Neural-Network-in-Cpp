//
// Created by Tommy Ludwig on 23.09.23.
//

#ifndef XORGATE_NEURALNETWORK_NET_H
#define XORGATE_NEURALNETWORK_NET_H
#include <vector>
#include "Neuron.h"

using namespace std;
typedef vector<Neuron> Layer;

class Net {
public:
    // topology is a vector of unsigned integers, it stands for the number of neurons in each layer
    explicit Net(const vector<unsigned> &topology);

    // FeedForward is used to calculate the output values
    void feedForward(const vector<double> &inputValues);

    // backPropagate is used to calculate the error and adjust the weights
    void backPropagate(const vector<double> &targetValues);

    // get results is used to get the output values
    void getResults(vector<double> &resultValues) const;

    [[nodiscard]] double getRecentAverageError() const;

private:
    vector<Layer> m_layers; // m_layers[layerNum][neuronNum]
    double m_error; // error is the average error of the output neurons
    double m_recentAverageError; // recentAverageError is the average error of the output neurons, but it is smoothed
    double m_recentAverageSmoothingFactor; // recentAverageSmoothingFactor is the smoothing factor for the recentAverageError
};


#endif //XORGATE_NEURALNETWORK_NET_H
