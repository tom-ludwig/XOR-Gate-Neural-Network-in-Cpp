//
// Created by Tommy Ludwig on 23.09.23.
//

#ifndef XORGATE_NEURALNETWORK_TRAININGDATA_H
#define XORGATE_NEURALNETWORK_TRAININGDATA_H


#include <string>
#include "fstream"
#include "sstream"

class TrainingData {
public:
    TrainingData(const std::string filename);

    bool isEof(void);

    void getTopology(std::vector<unsigned> &topology);

    unsigned getNextInputs(std::vector<double> &inputVals);

    unsigned getTargetOutputs(std::vector<double> &targetOutputVals);

private:
    std::ifstream m_trainingDataFile;
};


#endif //XORGATE_NEURALNETWORK_TRAININGDATA_H
