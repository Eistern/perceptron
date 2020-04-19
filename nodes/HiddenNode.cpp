#include <cmath>
#include "HiddenNode.h"

HiddenNode::HiddenNode(int connections, float (*activator)(float), float (*d_activator)(float))
        : _activator(activator), _d_activator(d_activator) {
    this->_weights = std::vector<float>(connections, 0.001f);
}

float HiddenNode::activate(float source) {
    return this->_activator(source);
}

float HiddenNode::activate_d(float source) {
    return this->_d_activator(source);
}

float HiddenNode::execute(const std::vector<float>& input) {
    float result = 0.0f;

    auto weightIter = this->_weights.begin();
    auto inputIter = input.begin();

    while (weightIter != this->_weights.end() && inputIter != input.end()) {
        if (!std::isnan(*inputIter))
            result += *weightIter * *inputIter;
        weightIter++;
        inputIter++;
    }

    return activate(result);
}

float HiddenNode::execute_d(const std::vector<float> &input) {
    float result = 0.0f;

    auto weightIter = this->_weights.begin();
    auto inputIter = input.begin();

    while (weightIter != this->_weights.end() && inputIter != input.end()) {
        if (!std::isnan(*inputIter))
            result += *weightIter * *inputIter;
        weightIter++;
        inputIter++;
    }

    return activate_d(result);
}

const std::vector<float> &HiddenNode::getWeights() const {
    return _weights;
}

float HiddenNode::getWeight(int index) const {
    return this->_weights[index];
}

void HiddenNode::update(const float learning_rate, const float delta, const std::vector<float> &prev_results) {
    if (std::isnan(delta))
        return;
    for (int i = 0; i < prev_results.size(); ++i) {
        if (!std::isnan(prev_results[i])) {
            this->_weights[i] += learning_rate * delta * prev_results[i];
        }
    }
}
