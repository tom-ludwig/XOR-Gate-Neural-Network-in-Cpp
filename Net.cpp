//
// Created by Tommy Ludwig on 23.09.23.
//

#include "Net.h"
#include "Neuron.h"
#include <iostream>
#include <cassert>

Net::Net(const vector<unsigned int> &topology) {
    unsigned numLayers = topology.size();
    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
        m_layers.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

        for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
            m_layers.back().push_back(Neuron(numOutputs, neuronNum));
            //cout << "Make a neuron in layer: " << layerNum << ". It has " << numOutputs << " outputs." << endl;
        }
        // Force the bias node output value to 1.0:
        m_layers.back().back().setOutputVal(1.0);
    }
}

// feedForward loops through the net and calculates the output values for each neuron
void Net::feedForward(const vector<double> &inputValues) {
    assert(inputValues.size() == m_layers[0].size() - 1);

    // assing (latch) the input values into the input neurons
    for (unsigned input = 0; input < inputValues.size(); ++input) {
        m_layers.front()[input].setOutputVal(inputValues[input]);
    }

    // note that we are starting at the second layer, because the first layer is the input layer
    for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {
        Layer &prevLayer = m_layers[layerNum - 1];
        for (unsigned neurons = 0; neurons < m_layers[layerNum].size(); ++neurons) {
            // the feedForward function is defined in Neuron.cpp, it is used to calculate the output values
            m_layers[layerNum][neurons].feedForward(prevLayer);
            cout << m_layers[layerNum][neurons].getOutputVal() << endl;
        }
    }
}
