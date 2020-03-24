#ifndef PERCEPTRON_FULLYCONNECTEDPERCEPTRON_H
#define PERCEPTRON_FULLYCONNECTEDPERCEPTRON_H

#include <vector>
#include "nodes/HiddenNode.h"

class FullyConnectedPerceptron {
private:
    constexpr static const float LEARNING_RATE = 0.01f;
    std::vector<std::vector<HiddenNode>> _layers;
    std::vector<std::vector<float>> _previousResult;

    std::vector<float> getForwardWeights(unsigned layer, int node);
public:
    void updateWeights(const std::vector<float>& expected);
    std::vector<float> iterate(const std::vector<float>& input);
    void addLayer(int n, const HiddenNode& nodeType);
};


#endif //PERCEPTRON_FULLYCONNECTEDPERCEPTRON_H
