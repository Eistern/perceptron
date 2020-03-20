#include "DatasetParser.h"

DatasetParser::DatasetParser(std::vector<std::string> nanValues) : _nanValues(std::move(nanValues)) {}

DatasetParser::DatasetParser(const std::vector<std::string>& nanValues, const std::string& name) : DatasetParser(nanValues) {
	loadFile(name);
}

void DatasetParser::loadFile(const std::string& name) {
    if (this->_fileStream.is_open()) {
        this->_fileStream.close();
    }

    this->_fileStream = std::ifstream(name, std::ifstream::binary);
}

void DatasetParser::closeFile() {
    if (!this->_fileStream.is_open()) {
        std::cerr << "File is not opened!" << std::endl;
        throw std::exception();
    }

    this->_fileStream.close();
};

void DatasetParser::loadParametersDefinition() {
    if (!this->_fileStream.is_open()) {
        std::cerr << "File is not opened!" << std::endl;
        throw std::exception();
    }

    this->_fileStream.seekg(0, std::ios_base::beg);
    std::string parametersDefinition;
    std::getline(this->_fileStream, parametersDefinition);
    this->_dataStart = this->_fileStream.tellg();

    this->_parametersDefinition = CSVUtils::parseLineToList(parametersDefinition, ';');
}

void DatasetParser::loadData() {
    if (!this->_fileStream.is_open() || this->_dataStart == 0)
        throw std::exception();

    this->_fileStream.seekg(0, std::ios_base::beg);
    this->_fileStream.seekg(this->_dataStart, std::ios_base::beg);

    this->_dataset.clear();

    std::string dataString;
    while (std::getline(this->_fileStream, dataString)) {
        this->_dataset.emplace_back(Data(this->_parametersDefinition, dataString, this->_nanValues));
    }
}

DatasetParser::~DatasetParser() {
    if (this->_fileStream.is_open()) {
        this->_fileStream.close();
    }
}

Dataset DatasetParser::initDataset() const {
    return Dataset(this->_parametersDefinition, this->_dataset);
}
