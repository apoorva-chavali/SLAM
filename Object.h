#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

// Object class/category to identify the object type
enum OBJECT_CLASS {
    PERSON,             // For people detection
    VEHICLE,            // For vehicle detection (cars, trucks, buses, motorcycles, etc.)
    BAG,                // For bag detection (backpack, handbag, suitcase, etc.)
    ANIMAL,             // For animal detection (cow, sheep, horse, dog, cat, bird, etc.)
    ELECTRONICS,        // For electronic device detection (cellphone, laptop, etc.)
    FRUIT_VEGETABLE,    // For fruit and vegetable detection (banana, apple, orange, carrot, etc.)
    SPORT               // For sport-related object detection (sport ball, etc.)
};

class Object {
private:
    std::string unique_object_id;
    std::vector<float> position; // 3D vector (x, y, z)
    std::vector<float> velocity; // 3D vector (vx, vy, vz)
    float confidence;
    OBJECT_CLASS label; // Object class/category

public:
    // Constructor with label
    Object(const std::string& id,
        const std::vector<float>& pos,
        const std::vector<float>& vel,
        float conf,
        OBJECT_CLASS obj_class);

    // Default constructor
    Object();

    // Destructor
    ~Object();

    // Getters
    std::string getId() const;
    std::vector<float> getPosition() const;
    std::vector<float> getVelocity() const;
    float getConfidence() const;
    OBJECT_CLASS getLabel() const;

    // Setters
    void setId(const std::string& id);
    void setPosition(const std::vector<float>& pos);
    void setVelocity(const std::vector<float>& vel);
    void setConfidence(float conf);
    void setLabel(OBJECT_CLASS obj_class);
};

#endif // OBJECT_H 
