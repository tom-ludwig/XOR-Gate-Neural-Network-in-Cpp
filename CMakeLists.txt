cmake_minimum_required(VERSION 3.26)
project(XORGate_NeuralNetwork)

set(CMAKE_CXX_STANDARD 23)

add_executable(XORGate_NeuralNetwork main.cpp
        Net.cpp
        Net.h
        Connection.cpp
        Connection.h
        Neuron.cpp
        Neuron.h
        TrainingData.cpp
        TrainingData.h)
