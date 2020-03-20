//
// Created by Daniil on 20.03.2020.
//

#include "FullyConnectedPerceptron.h"

void FullyConnectedPerceptron::addLayer(int n, const HiddenNode& nodeType) {
    std::vector<HiddenNode> nextLayer = std::vector<HiddenNode>(n, nodeType);

    this->_layers.push_back(nextLayer);
}
