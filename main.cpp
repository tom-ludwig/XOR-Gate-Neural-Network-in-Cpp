#include <iostream>
#include "vector"
#include "Net.h"

using namespace std;

int main() {
    vector<unsigned> topology = {2, 4, 1};
    Net myNet(topology);
    myNet.feedForward({1, 0});
    std::cout << "Done!" << std::endl;
    return 0;
}
