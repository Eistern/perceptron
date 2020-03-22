project(perceptron)

add_executable(perceptron main.cpp data/CSVUtils.h data/Data.cpp data/Data.h data/Dataset.cpp data/Dataset.h data/DatasetParser.h data/DatasetParser.cpp nodes/HiddenNode.cpp nodes/HiddenNode.h FullyConnectedPerceptron.cpp FullyConnectedPerceptron.h ActivationFunc.h)