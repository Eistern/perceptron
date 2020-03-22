#ifndef DATASET_PARSER_H
#define DATASET_PARSER_H

#include "CSVUtils.h"
#include "Data.h"
#include "Dataset.h"

#include <iostream>
#include <fstream>
#include <vector>

class DatasetParser {
private:
    std::vector<std::string> _nanValues;
	std::ifstream _fileStream;
	std::vector<std::string> _parametersDefinition;
	std::vector<Data> _dataset;
	unsigned int _dataStart = 0;
public:
    explicit DatasetParser(std::vector<std::string> nanValues);
	DatasetParser(const std::vector<std::string>& nanValues, const std::string& name);

	void loadFile(const std::string& name);
	void closeFile();
    void loadParametersDefinition();
    void loadData(const std::vector<std::string>& class_tags = std::vector<std::string>(0));

    Dataset initDataset() const;

	~DatasetParser();
};

#endif