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
    std::vector<std::string> classTags = {"G_total", "KGF"};

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

    for (const auto &clazz : classTags) {
        train.normalize_class(clazz);
        validation.normalize_class(clazz);
    }

    int firstLayerNum = 0;
    for (const std::string &parameter : test.getParamsNames()) {
        firstLayerNum += train.getValues(parameter).size();
    }

    FullyConnectedPerceptron perceptron;
    const int INPUT_CONNECTIONS = train.getParamsNames().size() - classTags.size();
    const int FIRST_LAYER = 50;
    const int SECOND_LAYER = 90;
    const int THIRD_LAYER = classTags.size();

    perceptron.addLayer(FIRST_LAYER, HiddenNode(INPUT_CONNECTIONS, ActivationFunc::sigmoid, ActivationFunc::dSigmoid));
    perceptron.addLayer(SECOND_LAYER, HiddenNode(FIRST_LAYER, ActivationFunc::sigmoid, ActivationFunc::dSigmoid));
    perceptron.addLayer(THIRD_LAYER, HiddenNode(SECOND_LAYER, ActivationFunc::sigmoid, ActivationFunc::dSigmoid));

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
                    err_r_t += (expected[i] - result[i]) * (expected[i] - result[i]);
            }
            perceptron.updateWeights(expected);
        }
        err_r_t /= 2.0f;

        printf("error on train:\t%.10f\t", err_r_t);

        for (const auto& validation_case : validation_data) {
            auto result = perceptron.iterate(validation_case.get_features_value());
            auto expected = validation_case.get_classes_value();
            for (int i = 0; i < result.size(); ++i) {
                if (!std::isnan(expected[i]))
                    err_r_v += (expected[i] - result[i]) * (expected[i] - result[i]);
            }
        }
        err_r_v /= 2.0f;

        printf("error on validation:\t%.10f\n", err_r_v);

        epoch_num++;
    }

    return 0;
}