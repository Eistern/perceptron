#ifndef PERCEPTRON_FULLYCONNECTEDPERCEPTRON_H
#define PERCEPTRON_FULLYCONNECTEDPERCEPTRON_H

#include <vector>
#include "nodes/HiddenNode.h"

class FullyConnectedPerceptron {
private:
    std::vector<std::vector<HiddenNode>> _layers;
public:
    void addLayer(int n, const HiddenNode& nodeType);
};


#endif //PERCEPTRON_FULLYCONNECTEDPERCEPTRON_H
