#include "FullyConnectedPerceptron.h"

#include <cmath>

void FullyConnectedPerceptron::addLayer(int n, const HiddenNode& nodeType) {
    std::vector<HiddenNode> nextLayer = std::vector<HiddenNode>(n, nodeType);

    this->_layers.push_back(nextLayer);
}

std::vector<float> FullyConnectedPerceptron::iterate(const std::vector<float>& input) {
    this->_previousResult.clear();
    this->_previousResult.push_back(input);
    std::vector<float> previous_input = input;

    for (auto layer : this->_layers) {
        auto node_it = layer.begin();
        std::vector<float> buff_v;
        buff_v.reserve(layer.size());

        for (auto node : layer) {
            buff_v.push_back(node.execute(previous_input));
        }
        previous_input = buff_v;
        this->_previousResult.push_back(buff_v);
    }

    return this->_previousResult.back();
}

std::vector<float> FullyConnectedPerceptron::getForwardWeights(unsigned layer, int node_index) {
    std::vector<float> result;
    std::vector<HiddenNode> next_layer = this->_layers[layer + 1];
    result.reserve(next_layer.size());
    for (const auto& node : next_layer) {
        result.push_back(node.getWeight(node_index));
    }
    return result;
}

void FullyConnectedPerceptron::updateWeights(const std::vector<float>& expected) {
    std::vector<float> result = this->_previousResult.back();
    std::vector<std::vector<float>> deltas;
    deltas.reserve(this->_layers.size());

    auto prev_layer_result = this->_previousResult.rbegin()++;
    auto r_layers = this->_layers.rbegin();

    auto expected_j = expected.begin();
    auto result_j = result.begin();

    float error_j;
    float delta_j;
    std::vector<float> deltas_j;
    deltas_j.reserve(r_layers->size());
    int j = 0;

    j = 0;
    while (expected_j != expected.end() && result_j != result.end()) {
        if (!std::isnan(*expected_j)) {
            error_j = (*expected_j - *result_j);
            delta_j = error_j * (*r_layers)[j].execute_d(*prev_layer_result);
            deltas_j.push_back(delta_j);
        } else {
            deltas_j.push_back(std::nanf(""));
        }
        j++;
        expected_j++;
        result_j++;
    }
    deltas.push_back(deltas_j);
    //GENERATED DELTAS FOR THE OUTPUT LAYER

    deltas_j.clear();
    prev_layer_result++;
    r_layers++;

    unsigned layer_num = this->_layers.size() - 2;

    auto deltas_it = deltas.begin();
    while (r_layers != this->_layers.rend()) {
        for (int i = 0; i < r_layers->size(); ++i) {
            std::vector<float> forward_weights = this->getForwardWeights(layer_num, i);
            error_j = 0.0f;
            for (int k = 0; k < forward_weights.size(); ++k) {
                if (!std::isnan((*deltas_it)[k])) {
                    error_j += (*deltas_it)[k] * forward_weights[k];
                }
            }
            delta_j = error_j * (*r_layers)[i].execute_d(*prev_layer_result);
            deltas_j.push_back(delta_j);
        }
        deltas.push_back(deltas_j);
        deltas_j.clear();

        deltas_it++;
        prev_layer_result++;
        r_layers++;
        layer_num--;
    }
    //GENERATED DELTAS FOR OTHER LAYERS

    for (int i = 0; i < this->_layers.size(); ++i) {
        for (int k = 0; k < this->_layers[i].size(); ++k) {
            this->_layers[i][k].update(FullyConnectedPerceptron::LEARNING_RATE, deltas[this->_layers.size() - 1 - i][k], this->_previousResult[i]);
        }
    }
    //UPDATE WEIGHTS FOR EACH LAYER
}
