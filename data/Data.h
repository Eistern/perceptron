#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <map>
#include <vector>

class Data {
private:
	std::map<std::string, float> _tags;
public:
	Data(const std::vector<std::string>& tagNames, std::string tagValues, std::vector<std::string> nanValues);
	Data(const Data& other);

	Data& operator=(const Data& other);
    Data& operator=(Data&& other) noexcept;

    float getTag(const std::string& tagName) const;

	~Data();
};

#endif