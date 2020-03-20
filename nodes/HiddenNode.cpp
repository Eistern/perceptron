#include <algorithm>
#include "HiddenNode.h"

HiddenNode::HiddenNode(int connections, float (*activator)(float)) : _activator(activator) {
    this->_weights = std::vector<float>(connections);
    std::fill(this->_weights.begin(), this->_weights.end(), 1);
}

float HiddenNode::activate(float source) {
    return this->_activator(source);
//    return 1.0f / (1.0f + std::exp(-1.0f * source));
}

float HiddenNode::execute(const std::vector<float>& input) {
    float result = 0.0f;

    auto weightIter = this->_weights.begin();
    auto inputIter = input.begin();

    while (weightIter != this->_weights.end() && inputIter != input.end()) {
        result += *weightIter * *inputIter;
        weightIter++;
        inputIter++;
    }

    return activate(result);
}

const std::vector<float> &HiddenNode::getWeights() const {
    return _weights;
}
