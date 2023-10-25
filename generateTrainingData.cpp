//
// Created by Tommy Ludwig on 25.10.23.
//
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int main() {
    cout << "topology: 2 4 1" << endl;
    for(int i = 10000; i >= 0; --i) {
        int n1 = (int) (2.0 * rand() / double(RAND_MAX));
        int n2 = (int) (2.0 * rand() / double(RAND_MAX));
        int t = n1 ^ n2; // bitwise XOR
        cout << "in: " << n1 << ".0 " << n2 << ".0 " << endl;
        cout << "out: " << t << ".0" << endl;
    }
}