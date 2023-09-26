# XOR Gate Neural Network in Cpp
This repository showcases a basic neural network designed to learn and predict the output of an XOR-Gate. It serves as an excellent introductory project for anyone looking to dive into the world of neural networks. Start your journey here with this simple yet fundamental 'Hello, World' example in neural networking.

<img width="457" alt="Screenshot 2023-09-22 at 5 05 50 PM" src="https://github.com/activcoding/XOR-Gate-Neural-Network-in-Cpp/assets/83090745/c4f6738b-8c86-4e2a-b9be-dd9079b7a72c">

<img width="457" alt="NeuralNet" src="https://github.com/activcoding/XOR-Gate-Neural-Network-in-Cpp/assets/83090745/ed81b4b4-7806-45c8-aae7-fee69d442b5f">


## Usage
1. `Fork` and `clone` the repo.
2. Follow the steps for generating the trianing data
3. Follow the steps to execute the code.

## Generate Training Data for a XOR-Gate
1. C++ file:
```cpp
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
```
```sh
g++ yourFileName.cpp -o makeTraingSamples
```
```sh
./makeTraingSamples > trainingData.txt
```
3. Move the `trainingData.txt` file into the projects folder.

## Run

1. `cd XORGate-NeuralNetwork`
2. Build project:
```sh
cmake --build cmake-build-debug
```
3. Run:
```sh
./cmake-build-debug/XORGate_NeuralNetwork
```
4. If the training file can't be found, check if the file is under the same diretory form where you execute the command. For example if you use CLion you properly have to move the file into the `cmake-build-debug` folder.
