#include <iostream>
#include <valarray>
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

    std::valarray<float> error_train = std::valarray<float>(classTags.size(), 1.0f);
    std::valarray<float> error_validation = std::valarray<float>(classTags.size(), 1.0f);
    float root_error = 0;
    int epoch_num = 0;

    std::vector<Data> train_data = train.getCases();
    std::vector<Data> validation_data = validation.getCases();
    while (error_train.max() > 0.01f || error_validation.max() > 0.01f) {
        error_train = 0.0f;
        error_validation = 0.0f;
        printf("Epoch %d:\t", epoch_num);

        for (const auto &train_case : train_data) {
            auto result = perceptron.iterate(train_case.get_features_value());
            auto expected = train_case.get_classes_value();
            for (int i = 0; i < result.size(); ++i) {
                if (!std::isnan(expected[i])) {
                    error_train[i] += (expected[i] - result[i]) * (expected[i] - result[i]);
                    root_error += (expected[i] - result[i]) * (expected[i] - result[i]);
                }
            }
            perceptron.updateWeights(expected);
        }
        error_train /= 2.0f;
        root_error /= train_data.size();
        root_error = std::sqrt(root_error);

        printf("error on train:\t%.10f\t", error_train.max());

        for (const auto &validation_case : validation_data) {
            auto result = perceptron.iterate(validation_case.get_features_value());
            auto expected = validation_case.get_classes_value();
            for (int i = 0; i < result.size(); ++i) {
                if (!std::isnan(expected[i]))
                    error_validation[i] += (expected[i] - result[i]) * (expected[i] - result[i]);
            }
            perceptron.updateWeights(expected);
        }
        error_validation /= 2.0f;

        printf("error on validation:\t%.10f\t", error_validation.max());
        printf("rmse for epoch:\t%.10f\n", root_error);

        epoch_num++;
    }

    return 0;
}