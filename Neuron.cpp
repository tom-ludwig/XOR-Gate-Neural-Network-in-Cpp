//
// Created by Tommy Ludwig on 23.09.23.
//

#include "Neuron.h"
#include "Connection.h"
#include "iostream"

Neuron::Neuron(unsigned int numOutputs, unsigned int myIndex) {
    for (unsigned connection = 0; connection < numOutputs; ++connection) {
        m_outputWeights.push_back(Connection()); // a random weight is assigned in the Connection constructor

        m_myIndex = myIndex;
    }
}

double Neuron::eta = 0.5; // overall net learning rate, [0.0..1.0]; 0.0 means: no learning, 1.0 means: learn at full
double Neuron::alpha = 0.5; // momentum, multiplier of last deltaWeight, [0.0..n]; 0.0 means: no momentum, 0.5 means:

void Neuron::setOutputVal(double value) {
    m_outputVal = value;
}

double Neuron::getOutputVal() const {
    return m_outputVal;
}

// this function is used for calculating the output of the neurons
void Neuron::feedForward(const vector<Neuron> &prevLayer) {
    double sum = 0.0;

    // print all the weights
    for (unsigned neuron = 0; neuron < prevLayer.size(); ++neuron) {
        /*std::cout << "Neuron " << m_myIndex << " weight " << neuron << ": " << prevLayer[neuron]
        .m_outputWeights[m_myIndex].weight << std::endl;
         */
    }
    for (unsigned neuron = 0; neuron < prevLayer.size(); ++neuron) {
        sum += prevLayer[neuron].getOutputVal() * prevLayer[neuron].m_outputWeights[m_myIndex].weight;
    }

    m_outputVal = Neuron::transferFunction(sum);
    //m_outputVal = Neuron::sigmoid(sum);
    //std::cout << "Neuron " << m_myIndex << " output: " << m_outputVal << std::endl;
}

double Neuron::sigmoid(double x) {
    //sigmoid function
    return 1 / (1 + exp(-x));
}

double Neuron::transferFunction(double x) {
    return tanh(x);
}

void Neuron::calculateOutputGradients(double targetValue) {
    double delta = targetValue - m_outputVal;
    m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calculateHiddenGradients(const vector<Neuron> &nextLayer) {
    double sum = 0.0;

    for (unsigned neuron = 0; neuron < nextLayer.size() - 1; ++neuron) {
        sum += m_outputWeights[neuron].weight * nextLayer[neuron].m_gradient;
    }

    m_gradient = sum * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::updateInputWeights(vector<Neuron> &prevLayer) const {
    // n stands for the index of the neuron
    for (unsigned n = 0; n < prevLayer.size(); ++n) {
        Neuron &neuron = prevLayer[n];
        cout << "Old weight: " << neuron.m_outputWeights[m_myIndex].weight << endl;
        cout << "Old delta weight: " << neuron.m_outputWeights[m_myIndex].deltaWeight << endl;

        double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

        // TODO: Implement quicker method;
        double newDeltaWeight = eta * neuron.getOutputVal() * m_gradient + alpha * oldDeltaWeight;

        neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
        neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;

        cout << "New weight: " << neuron.m_outputWeights[m_myIndex].weight << endl;
        cout << "New delta weight: " << neuron.m_outputWeights[m_myIndex].deltaWeight << endl;
    }
}

vector<Connection> Neuron::getOutputWeights() const {
    return m_outputWeights;
}

double Neuron::transferFunctionDerivative(double x) {
    return 1 - x * x;
}
