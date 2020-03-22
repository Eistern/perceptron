#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <vector>
#include <string>

class CSVUtils {
public:
    static std::vector<std::string> parseLineToList(std::string from, char delimiter) {
        std::vector<std::string> result;

        std::string token;
        int pos;

        while ((pos = from.find(delimiter)) != std::string::npos) {
            token = from.substr(0, pos);
            from.erase(0, pos + 1);
            result.emplace_back(token);
        }
        result.push_back(from);

        return result;
    }
};

#endif