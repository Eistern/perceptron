#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <map>
#include <vector>

class Data {
private:
	std::map<std::string, float> _features;
	std::map<std::string, float> _classes;
public:
	Data(const std::vector<std::string>& tagNames, std::string tagValues, std::vector<std::string> classTags, std::vector<std::string> nanValues);
	Data(const Data& other);

	Data& operator=(const Data& other);
    Data& operator=(Data&& other) noexcept;

    float get_feature(const std::string& feature_name) const;

    std::vector<float> get_classes_value() const;
    std::vector<float> get_features_value() const;

	~Data();
};

#endif