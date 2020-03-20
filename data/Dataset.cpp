#include "Dataset.h"

#include <utility>
#include <cmath>
#include <algorithm>


Dataset::Dataset(std::vector<std::string> parametersNames, std::vector<Data> data) : _params(std::move(parametersNames)), _set(std::move(data)) {}

float Dataset::getEntropy() const {
    float result = 0.0;
    auto length = (float) getSize();

    for (auto& caseCount :  this->_counts) {
        float probability = (float) caseCount.second / length;
        result -= (probability) * log2f(probability);
    }
    return result;
}

int Dataset::getSize() const {
    return this->_set.size();
}

std::vector<float> Dataset::getValues(const std::string &parameter) const {
    std::vector<float> result;

    for (auto& record : this->_set) {
        float tagValue = record.getTag(parameter);
        if (std::find(result.begin(), result.end(), tagValue) == result.end()) {
            result.push_back(tagValue);
        }
    }

    return result;
}

const std::vector<std::string> &Dataset::getParamsNames() const {
    return this->_params;
}

const std::vector<Data> &Dataset::getCases() const {
    return this->_set;
}

Dataset::Dataset(const Dataset &other) = default;

Dataset::~Dataset() = default;
