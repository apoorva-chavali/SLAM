#include "ObjectParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

ObjectParser::ObjectParser() {
    // No initialization needed
}

ObjectParser::~ObjectParser() {
    // No cleanup needed
}

std::vector<Object> ObjectParser::parseFile(const std::string& filename) {
    std::vector<Object> objects;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return objects;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                objects.push_back(parseLine(line));
            }
            catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
            }
        }
    }

    file.close();
    return objects;
}

Object ObjectParser::parseLine(const std::string& line) {
    std::stringstream ss(line);
    std::string token;

    // Parse object class
    if (!std::getline(ss, token, ';')) {
        throw std::runtime_error("Missing object class");
    }
    OBJECT_CLASS objClass = stringToObjectClass(token);

    // Parse object ID
    if (!std::getline(ss, token, ';')) {
        throw std::runtime_error("Missing object ID");
    }
    std::string id = token;

    // Parse position vector
    if (!std::getline(ss, token, ';')) {
        throw std::runtime_error("Missing position");
    }
    std::vector<float> position = parseVector(token);

    // Parse velocity vector
    if (!std::getline(ss, token, ';')) {
        throw std::runtime_error("Missing velocity");
    }
    std::vector<float> velocity = parseVector(token);

    // Parse confidence
    if (!std::getline(ss, token, ';')) {
        throw std::runtime_error("Missing confidence");
    }
    float confidence;
    try {
        confidence = std::stof(token);
    }
    catch (...) {
        throw std::runtime_error("Invalid confidence value");
    }

    // Create and return object
    return Object(id, position, velocity, confidence, objClass);
}

OBJECT_CLASS ObjectParser::stringToObjectClass(const std::string& str) {
    if (str == "PERSON") return PERSON;
    if (str == "VEHICLE") return VEHICLE;
    if (str == "STOP") return STOP;
    if (str == "PED_CROSSING") return PED_CROSSING;
    if (str == "DNE") return DNE;

    throw std::runtime_error("Unknown object class: " + str);
}

std::vector<float> ObjectParser::parseVector(const std::string& vectorStr) {
    std::vector<float> result;
    std::stringstream ss(vectorStr);
    std::string component;

    while (std::getline(ss, component, ',')) {
        try {
            result.push_back(std::stof(component));
        }
        catch (...) {
            throw std::runtime_error("Invalid vector component: " + component);
        }
    }

    if (result.size() != 3) {
        throw std::runtime_error("Vector must have exactly 3 components");
    }

    return result;
}