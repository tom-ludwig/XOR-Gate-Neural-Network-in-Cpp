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
        m_layers[0][input].setOutputVal(inputValues[input]);
    }

    // note that we are starting at the second layer, because the first layer is the input layer
    for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {
        Layer &prevLayer = m_layers[layerNum - 1];
        for (unsigned neurons = 0; neurons < m_layers[layerNum].size(); ++neurons) {
            // the feedForward function is defined in Neuron.cpp, it is used to calculate the output values
            m_layers[layerNum][neurons].feedForward(prevLayer);
            //cout << m_layers[layerNum][neurons].getOutputVal() << endl;
        }
    }
}

// BackPropagate is used to calculate the error and adjust the weights; Basically, it is the process of training.
void Net::backPropagate(const vector<double> &targetValues) {

    Layer &outputLayer = m_layers.back();
    m_error = 0.0;

    for (unsigned neuron = 0; neuron < outputLayer.size() - 1; ++neuron) {
        double delta = targetValues[neuron] - outputLayer[neuron].getOutputVal(); // delta is the difference between the target value and the actual value
        m_error += delta * delta;
    }

    // calculate the average error squared
    m_error /= outputLayer.size() - 1;
    m_error = sqrt(m_error); // RMS(Root Mean Square Error)

    // implement a recent average measurement
    m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) /
                           (m_recentAverageSmoothingFactor + 1.0);

    // Calculate output layer gradients
    for (unsigned neuron = 0; neuron < outputLayer.size() - 1; ++neuron) {
        // TODO: Move this to the upper loop
        outputLayer[neuron].calculateOutputGradients(targetValues[neuron]);
    }


    // Calculate gradients on hidden layers
    // TODO: Check if the loop starts at the output layer or the first hidden layer;
    for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum) {
        Layer &hiddenLayer = m_layers[layerNum];
        Layer &nextLayer = m_layers[layerNum + 1];

        for (auto & neuron : hiddenLayer) {
            neuron.calculateHiddenGradients(nextLayer);
        }
    }

    for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum) {
        Layer &currentLayer = m_layers[layerNum];
        Layer &prevLayer = m_layers[layerNum - 1];
        for (auto & neuron : currentLayer) {
            //cout << "Update weights for neuron " << neuron.getOutputVal() << endl;
            neuron.updateInputWeights(prevLayer);
        }
    }
}

void Net::getResults(vector<double> &resultValues) const {
    resultValues.clear();

    for (unsigned n = 0; n < m_layers.back().size() - 1; ++n) {
        resultValues.push_back(m_layers.back()[n].getOutputVal());
    }
    cout << "Result: " << endl;
    for (auto & resultValue : resultValues) {
        // if result value is smaller than 0.001, set it to 0
        // if result is bigger than 0.9, set it to 1
        if (resultValue < 0.001) {
            cout << "0" << endl;
        } else if (resultValue > 0.9) {
            cout << "1" << endl;
        }
    }
}

[[nodiscard]] double Net::getRecentAverageError() const {
    return m_recentAverageError;
}







