//
// Created by Tommy Ludwig on 23.09.23.
//

#include "Connection.h"
#include <cstdlib>

Connection::Connection()  {
    weight = randomWeight();
    deltaWeight = 0; // deltaWeight is the change in weight of the connection
}

double Connection::randomWeight() {
    return rand() / double(RAND_MAX);
}
