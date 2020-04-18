#include "Data.h"

#include <utility>
#include <cmath>
#include <algorithm>

Data::Data(const std::vector<std::string>& tagNames, std::string tagValues, std::vector<std::string> classTags, std::vector<std::string> nanValues) {
	this->_features = std::map<std::string, float>();

	size_t pos = 0;
	std::string token;
	auto namesIterator = tagNames.begin();

	while (namesIterator != tagNames.end()) {
        pos = tagValues.find(';');
		token = tagValues.substr(0, pos);
		auto pair = std::pair<std::string, float>(*namesIterator, std::find(nanValues.begin(), nanValues.end(), token) != nanValues.end() ? std::nanf("") : std::stof(token));
		if (std::find(classTags.begin(), classTags.end(), *(namesIterator)) == classTags.end())
		    this->_features.insert(pair);
        else
            this->_classes.insert(pair);
		tagValues.erase(0, pos + 1);
		namesIterator++;
	}
}

Data::Data(const Data &other) = default;

Data &Data::operator=(const Data &other) {
    if (this != &other) {
        this->_features = other._features;
    }
    return *this;
}

float Data::get_feature(const std::string &feature_name) const {
    auto result = this->_features.find(feature_name);
    if (result == this->_features.end())
        throw std::exception();

    return result->second;
}

Data &Data::operator=(Data &&other) noexcept {
    if (this != &other) {
        this->_features = std::move(other._features);
    }
    return *this;
}

std::vector<float> Data::get_classes_value() const {
    std::vector<float> result;
    result.reserve(this->_classes.size());
    for (const auto& clazz : this->_classes) {
        result.push_back(clazz.second);
    }
    return result;
}

std::vector<float> Data::get_features_value() const {
    std::vector<float> result;
    result.reserve(this->_features.size());
    for (const auto &feature : this->_features) {
        result.push_back(feature.second);
    }
    return result;
}

void Data::set_class_value(const std::string &clazz, float value) {
    this->_classes[clazz] = value;
}

float Data::get_clazz(const std::string &class_name) const {
    auto result = this->_classes.find(class_name);
    if (result == this->_classes.end())
        throw std::exception();

    return result->second;
}

Data::~Data() = default;
