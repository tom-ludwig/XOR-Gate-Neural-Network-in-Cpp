//
// Created by Tommy Ludwig on 23.09.23.
//

#ifndef XORGATE_NEURALNETWORK_NEURON_H
#define XORGATE_NEURALNETWORK_NEURON_H

#include <vector>
#include "Connection.h"

using namespace std;

class Neuron {
public:
    Neuron(unsigned numOutputs, unsigned myIndex);

    void setOutputVal(double value);

    double getOutputVal() const;

    // this function is used for calculating the output of the neurons
    void feedForward(const vector<Neuron> &prevLayer);

    // used by the backpropagation, calculate the gradient (Steigung) of the output neurons
    void calculateOutputGradients(double targetValue);

    // the difference to the output neurons is that the hidden neurons don't have a target value
    void calculateHiddenGradients(const vector<Neuron> &nextLayer);

    void updateInputWeights(vector<Neuron> &prevLayer) const;

    vector<Connection> getOutputWeights() const;

private:
    unsigned m_myIndex;
    double m_outputVal;
    vector<Connection> m_outputWeights;
    double m_gradient; // used by the backpropagation, gradient of the error function, which is the slope of the error function

    static double eta;
    static double alpha;

    static double sigmoid(double x); // output range [0.0..1.0], smooth curve
    static double transferFunction(double x); // tanh - output range [-1.0..1.0], smooth curve
    static double transferFunctionDerivative(double x); // tanh derivative
    double sumDOW(const vector<Neuron> &nextLayer) const; // sum of the derivatives of the weights of the next layer
};


#endif //XORGATE_NEURALNETWORK_NEURON_H
