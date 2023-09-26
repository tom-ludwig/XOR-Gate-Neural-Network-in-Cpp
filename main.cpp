#include <iostream>
#include "vector"
#include "Net.h"
#include "TrainingData.h"
#include "cassert"

// The command for listing all file in the terminal is: ls -a
// if you only want to see files with a specific ending, e.g., .txt, you can use: ls -a *.txt

using namespace std;

void showVectorVals(std::string label, std::vector<double> &v) {
    std::cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
}

int main() {
    TrainingData trainingData("shortTrainingData.txt");
    std::cout << "Finished reading training data" << std::endl;
    // e.g., { 3, 2, 1 } means 3 neurons in the input layer, 2 in the hidden layer, and 1 in the output layer
    std::vector<unsigned> topology;
    trainingData.getTopology(topology);
    std::cout << topology[1] << std::endl;
    std::cout << "Finished reading topology" << std::endl;
    Net myNet(topology);
    std::cout << "Finished creating the NET" << std::endl;

    std::vector<double> inputVals, targetVals, resultVals;
    int trainingPass = 0;

    while (!trainingData.isEof()) {
        ++trainingPass;
        std::cout << std::endl << "Pass: " << trainingPass;

        // Get new input data and feed it forward;
        if (trainingData.getNextInputs(inputVals) != topology[0]) {
            break;
        }
        showVectorVals("; Inputs:", inputVals);
        myNet.feedForward(inputVals);

        myNet.getResults(resultVals);
        showVectorVals("Outputs:", resultVals);

        trainingData.getTargetOutputs(targetVals);
        showVectorVals("Targets: ", targetVals);
        assert(targetVals.size() == topology.back());

        myNet.backPropagate(targetVals);

        std::cout << "Net recent average error: " << myNet.getRecentAverageError() << std::endl;
    }

    std::cout << std::endl << "Training done! Starting testing:" << std::endl;

    cout << endl << "0 and 1:" << endl;
    std::vector<double> testVals = {0, 1};
    myNet.feedForward(testVals);
    myNet.getResults(testVals);

    cout << endl << "1 and 0:" << endl;
    testVals = {1, 0};
    myNet.feedForward(testVals);
    myNet.getResults(testVals);

    cout << endl << "1 and 1:" << endl;
    testVals = {1, 1};
    myNet.feedForward(testVals);
    myNet.getResults(testVals);

    cout << endl << "0 and 0:" << endl;
    testVals = {0, 0};
    myNet.feedForward(testVals);
    myNet.getResults(testVals);

    showVectorVals("Test results: ", testVals);
    cout << myNet.getRecentAverageError() << endl;

    return 0;
}
