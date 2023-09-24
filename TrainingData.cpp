//
// Created by Tommy Ludwig on 23.09.23.
//

#include "TrainingData.h"
#include "vector"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

TrainingData::TrainingData(const std::string filename) {
    std::cout << "Searched in: " << fs::current_path() << std::endl;
    m_trainingDataFile.open(filename.c_str());

    if (!m_trainingDataFile.is_open()) {
        std::cout << "Error: training data file not found" << std::endl;
        abort();
    } else {
        std::cout << "training data file found" << std::endl;
    }

}

void TrainingData::getTopology(std::vector<unsigned> &topology) {
    std::string line;
    std::string label;

    std::getline(m_trainingDataFile, line);
    std::stringstream ss(line);
    std::cout << "line: " << line << std::endl;
    ss >> label;
    std::cout << "label: " << label << std::endl;

    if (this->isEof() || label.compare("topology:") != 0) {
        std::cout << "Error: topology not found" << std::endl;
        abort();
    }
    std::cout << "topology found" << std::endl;
    while (!ss.eof()) {
        std::cout << "in while loop" << std::endl;
        unsigned n;
        ss >> n;
        std::cout << "n: " << n << std::endl;
        topology.push_back(n);
    }
    std::cout << "topology size: " << topology.size() << std::endl;
    return;
}

bool TrainingData::isEof(void) {
    return false;
}

unsigned TrainingData::getNextInputs(std::vector<double> &inputVals) {
    inputVals.clear();

    std::string line;
    getline(m_trainingDataFile, line);
    std::stringstream ss(line);

    std::string label;
    ss >> label;
    if (label.compare("in:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            inputVals.push_back(oneValue);
        }
    }

    return inputVals.size();
}

unsigned TrainingData::getTargetOutputs(std::vector<double> &targetOutputVals) {
    targetOutputVals.clear();

    std::string line;
    std::getline(m_trainingDataFile, line);
    std::stringstream ss(line);

    std::string label;
    ss >> label;
    if (label.compare("out:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            targetOutputVals.push_back(oneValue);
        }
    }
    return targetOutputVals.size();
}