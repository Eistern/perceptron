#ifndef PERCEPTRON_ACTIVATIONFUNC_H
#define PERCEPTRON_ACTIVATIONFUNC_H

#include <cmath>

class ActivationFunc {
public:
    static float sigmoid(float input) {
        return 1.0f / (1.0f + std::exp(-1.0f * input));
    }

    static float dSigmoid(float input) {
        return sigmoid(input) * (1.0f - sigmoid(input));
    }

    static float id(float input) {
        return input;
    }

    static float dId(float input) {
        return 1.0f;
    }
};

#endif //PERCEPTRON_ACTIVATIONFUNC_H
