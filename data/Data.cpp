#include "Data.h"

#include <utility>
#include <cmath>
#include <algorithm>

Data::Data(const std::vector<std::string>& tagNames, std::string tagValues, std::vector<std::string> nanValues) {
	this->_tags = std::map<std::string, float>();

	size_t pos = 0;
	std::string token;
	auto namesIterator = tagNames.begin();

	while (namesIterator != tagNames.end()) {
        pos = tagValues.find(';');
		token = tagValues.substr(0, pos);
		this->_tags.insert(std::pair<std::string, float>(*namesIterator, std::find(nanValues.begin(), nanValues.end(), token) != nanValues.end() ? std::nanf("") : std::stof(token)));
		tagValues.erase(0, pos + 1);
		namesIterator++;
	}
}

Data::Data(const Data &other) = default;

Data &Data::operator=(const Data &other) {
    if (this != &other) {
        this->_tags = other._tags;
    }
    return *this;
}

float Data::getTag(const std::string &tagName) const {
    auto result = this->_tags.find(tagName);
    if (result == this->_tags.end())
        throw std::exception();

    return result->second;
}

Data &Data::operator=(Data &&other) noexcept {
    if (this != &other) {
        this->_tags = std::move(other._tags);
    }
    return *this;
}

Data::~Data() = default;
