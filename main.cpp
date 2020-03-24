#include <iostream>
#include "data/DatasetParser.h"
#include "FullyConnectedPerceptron.h"
#include "ActivationFunc.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: ./perceptron <training_data> <validation_data> <test_data>" << std::endl;
        return 1;
    }

    DatasetParser parser({"", "-"});
    std::vector<std::string> classTags = {"Udel'naya plotnost' gaza ", "G_total", "KGF"};

    parser.loadFile(argv[1]);
    parser.loadParametersDefinition();
    parser.loadData(classTags);

    Dataset train = parser.initDataset();
    parser.closeFile();

    parser.loadFile(argv[2]);
    parser.loadParametersDefinition();
    parser.loadData(classTags);

    Dataset validation = parser.initDataset();
    parser.closeFile();

    parser.loadFile(argv[3]);
    parser.loadParametersDefinition();
    parser.loadData();

    Dataset test = parser.initDataset();
    parser.closeFile();

    int firstLayerNum = 0;
    for (const std::string &parameter : test.getParamsNames()) {
        firstLayerNum += train.getValues(parameter).size();
    }

    FullyConnectedPerceptron perceptron;
    perceptron.addLayer(firstLayerNum,
                        HiddenNode(test.getParamsNames().size(), ActivationFunc::sigmoid, ActivationFunc::dSigmoid));
    perceptron.addLayer(90, HiddenNode(firstLayerNum, ActivationFunc::sigmoid, ActivationFunc::dSigmoid));
    perceptron.addLayer(3, HiddenNode(90, ActivationFunc::id, ActivationFunc::dId));

    float err_r_t = 1.0f;
    float err_r_v = 1.0f;
    int epoch_num = 0;

    std::vector<Data> train_data = train.getCases();
    std::vector<Data> validation_data = validation.getCases();
    while (err_r_t > 0.01f || err_r_v > 0.01f) {
        err_r_t = 0.0f;
        err_r_v = 0.0f;
        printf("Epoch %d:\t", epoch_num);

        for (const auto& train_case : train_data) {
            auto result = perceptron.iterate(train_case.get_features_value());
            auto expected = train_case.get_classes_value();
            for (int i = 0; i < result.size(); ++i) {
                if (!std::isnan(expected[i]))
                    err_r_t += std::abs(expected[i] - result[i]);
            }
            perceptron.updateWeights(expected);
        }
        err_r_t /= train_data.size();

        printf("error on train:\t%.10f\t", err_r_t);

        for (const auto& validation_case : validation_data) {
            auto result = perceptron.iterate(validation_case.get_features_value());
            auto expected = validation_case.get_classes_value();
            for (int i = 0; i < result.size(); ++i) {
                if (!std::isnan(expected[i]))
                    err_r_v += std::abs(expected[i] - result[i]);
            }
        }
        err_r_v /= validation_data.size();

        printf("error on validation:\t%.10f\n", err_r_v);

        epoch_num++;
    }

    return 0;
}