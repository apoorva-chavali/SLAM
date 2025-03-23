#ifndef OBJECT_PARSER_H
#define OBJECT_PARSER_H

#include "Object.h"
#include <string>
#include <vector>

class ObjectParser {
public:
    // Constructor and destructor
    ObjectParser();
    ~ObjectParser();

    // Parse a file and return vector of Object instances
    std::vector<Object> parseFile(const std::string& filename);

    // Parse a single line and return an Object instance
    Object parseLine(const std::string& line);

private:
    // Helper methods
    OBJECT_CLASS stringToObjectClass(const std::string& str);
    std::vector<float> parseVector(const std::string& vectorStr);
};

#endif // OBJECT_PARSER_H 
