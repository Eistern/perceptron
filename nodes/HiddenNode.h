#ifndef PERCEPTRON_HIDDENNODE_H
#define PERCEPTRON_HIDDENNODE_H


#include <vector>

class HiddenNode {
private:
    std::vector<float> _weights;
    float (*_activator)(float);

    float activate(float source);
public:
    HiddenNode(int connections, float (*activator)(float));

    float execute(const std::vector<float>& input);

    const std::vector<float> &getWeights() const;
};


#endif //PERCEPTRON_HIDDENNODE_H
