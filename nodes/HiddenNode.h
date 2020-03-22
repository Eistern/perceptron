#ifndef PERCEPTRON_HIDDENNODE_H
#define PERCEPTRON_HIDDENNODE_H


#include <vector>

class HiddenNode {
private:
    std::vector<float> _weights;
    float (*_activator)(float);
    float (*_d_activator)(float);
public:
    HiddenNode(int connections, float (*activator)(float), float (*d_activator)(float));

    float execute(const std::vector<float>& input);
    float execute_d(const std::vector<float>& input);

    float activate(float source);
    float activate_d(float source);

    const std::vector<float> &getWeights() const;
    float getWeight(int index) const;

    void update(float learning_rate, float delta, const std::vector<float>& prev_results);
};


#endif //PERCEPTRON_HIDDENNODE_H
