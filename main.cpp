#include <iostream>
#include "vector"
#include "Net.h"

using namespace std;

int main() {
    vector<unsigned> topology = {2, 4, 1};
    Net myNet(topology);
    myNet.feedForward({1, 0});

    vector<double> resultVals;
    myNet.getResults(resultVals);

    for (unsigned i = 0; i < 50; ++i) {
        myNet.feedForward({1, 0});
        myNet.backPropagate({1});
    }
    myNet.feedForward({1, 0});
    myNet.getResults(resultVals);

    for (unsigned i = 0; i < 50; ++i) {
        myNet.feedForward({1, 1});
        myNet.backPropagate({0});
    }
    myNet.feedForward({0, 0});
    myNet.getResults(resultVals);
    std::cout << "Done!" << std::endl;
    return 0;
}
