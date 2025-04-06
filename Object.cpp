#include "Object.h"
#include <GeographicLib/Geodesic.hpp>
#include <cmath>

Object::Object(const std::string& id,
    const std::vector<float>& pos,
    const std::vector<float>& vel,
    float conf,
    OBJECT_CLASS obj_class) :
    unique_object_id(id),
    position(pos),
    velocity(vel),
    confidence(conf),
    label(obj_class),
    latitude(0.0),
    longitude(0.0) {
}

Object::Object() :
    unique_object_id(""),
    position({ 0.0f, 0.0f, 0.0f }),
    velocity({ 0.0f, 0.0f, 0.0f }),
    confidence(0.0f),
    label(PERSON),
    latitude(0.0),
    longitude(0.0) {
}

Object::~Object() {}

std::string Object::getId() const { return unique_object_id; }
std::vector<float> Object::getPosition() const { return position; }
std::vector<float> Object::getVelocity() const { return velocity; }
float Object::getConfidence() const { return confidence; }
OBJECT_CLASS Object::getLabel() const { return label; }
double Object::getLatitude() const { return latitude; }
double Object::getLongitude() const { return longitude; }

void Object::setId(const std::string& id) { unique_object_id = id; }
void Object::setPosition(const std::vector<float>& pos) { position = pos; }
void Object::setVelocity(const std::vector<float>& vel) { velocity = vel; }
void Object::setConfidence(float conf) { confidence = conf; }
void Object::setLabel(OBJECT_CLASS obj_class) { label = obj_class; }
void Object::setLatLon(double lat, double lon) {
    latitude = lat;
    longitude = lon;
}

void Object::computeLatLonFromDisplacement(double originLat, double originLon, double headingDegrees) {
    using GeographicLib::Geodesic;
    using GeographicLib::Math;

    float dx = position[0];  // East
    float dy = position[1];  // North

    // Compute displacement vector's azimuth (heading)
    double azimuthRad = std::atan2(dx, dy); // Note: atan2(x, y) to get heading from north
    double azimuthDeg = azimuthRad * (180.0 / M_PI);  // Convert to degrees

    // Apply frame heading offset (if vehicle is not aligned with true north)
    double trueAzimuth = azimuthDeg + headingDegrees;

    // Total displacement (2D)
    double distance = std::sqrt(dx * dx + dy * dy); // in meters

    const Geodesic& geo = Geodesic::WGS84();
    double newLat, newLon;
    geo.Direct(originLat, originLon, trueAzimuth, distance, newLat, newLon);

    latitude = newLat;
    longitude = newLon;
}
