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
        std::cout << "Neuron " << m_myIndex << " weight " << neuron << ": " << prevLayer[neuron].m_outputWeights[m_myIndex].weight << std::endl;
    }
    for (unsigned neuron = 0; neuron < prevLayer.size(); ++neuron) {
        sum += prevLayer[neuron].getOutputVal() * prevLayer[neuron].m_outputWeights[m_myIndex].weight;
    }

    m_outputVal = Neuron::transferFunction(sum);
    //m_outputVal = Neuron::sigmoid(sum);
    std::cout << "Neuron " << m_myIndex << " output: " << m_outputVal << std::endl;
}

double Neuron::sigmoid(double x) {
    //sigmoid function
    return 1 / (1 + exp(-x));
}

double Neuron::transferFunction(double x) {
    return tanh(x);
}
