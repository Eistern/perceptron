#ifndef C45_DATASET_H
#define C45_DATASET_H

#include "Data.h"

#include <string>
#include <vector>

class Dataset {
private:
    std::vector<std::string> _params;
    std::vector<Data> _set;
    std::map<std::string, int> _counts;

    void _generateCounts();
public:
    Dataset(std::vector<std::string> parametersNames, std::vector<Data> data);
    Dataset(const Dataset& other);

    std::vector<float> getValues(const std::string& parameter) const;

    float getEntropy() const;
    int getSize() const;
    const std::vector<std::string>& getParamsNames() const;
    const std::vector<Data>& getCases() const;

    ~Dataset();
};


#endif //C45_DATASET_H
