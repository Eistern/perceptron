#include <iostream>
#include "data/DatasetParser.h"
#include "FullyConnectedPerceptron.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: ./perceptron <training_data> <validation_data>" << std::endl;
        return 1;
    }

    DatasetParser parser({"", "-"});

    parser.loadFile(argv[1]);
    parser.loadParametersDefinition();
    parser.loadData();

    Dataset train = parser.initDataset();

    parser.loadFile(argv[2]);
    parser.loadParametersDefinition();
    parser.loadData();

    Dataset validation = parser.initDataset();

    FullyConnectedPerceptron perceptron;


    return 0;
}