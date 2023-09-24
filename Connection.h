//
// Created by Tommy Ludwig on 23.09.23.
//

#ifndef XORGATE_NEURALNETWORK_CONNECTION_H
#define XORGATE_NEURALNETWORK_CONNECTION_H


class Connection {
public:
    Connection();
    double weight; // weight is the weight of the connection
    double deltaWeight{}; // deltaWeight is the change in weight of the connection
    static double randomWeight();
};


#endif //XORGATE_NEURALNETWORK_CONNECTION_H
