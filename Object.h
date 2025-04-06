#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

// Object class/category to identify the object type
enum OBJECT_CLASS {
    PERSON,
    VEHICLE,
    STOP,
    PED_CROSSING,
    DNE
};

class Object {
private:
    std::string unique_object_id;
    std::vector<float> position; // 3D vector (x, y, z)
    std::vector<float> velocity; // 3D vector (vx, vy, vz)
    float confidence;
    OBJECT_CLASS label;

    // New fields
    double latitude;
    double longitude;

public:
    // Constructor
    Object(const std::string& id,
        const std::vector<float>& pos,
        const std::vector<float>& vel,
        float conf,
        OBJECT_CLASS obj_class);

    Object(); // Default constructor
    ~Object();

    // Getters
    std::string getId() const;
    std::vector<float> getPosition() const;
    std::vector<float> getVelocity() const;
    float getConfidence() const;
    OBJECT_CLASS getLabel() const;
    double getLatitude() const;
    double getLongitude() const;

    // Setters
    void setId(const std::string& id);
    void setPosition(const std::vector<float>& pos);
    void setVelocity(const std::vector<float>& vel);
    void setConfidence(float conf);
    void setLabel(OBJECT_CLASS obj_class);
    void setLatLon(double lat, double lon);

    // New method
    void computeLatLonFromDisplacement(double originLat, double originLon, double headingDegrees = 0.0);
};

#endif // OBJECT_H
