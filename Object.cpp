 #include "Object.h"

// Constructor with label
Object::Object(const std::string& id,
    const std::vector<float>& pos,
    const std::vector<float>& vel,
    float conf,
    OBJECT_CLASS obj_class) :
    unique_object_id(id),
    position(pos),
    velocity(vel),
    confidence(conf),
    label(obj_class) {
}

// Default constructor
Object::Object() :
    unique_object_id(""),
    position({ 0.0f, 0.0f, 0.0f }),
    velocity({ 0.0f, 0.0f, 0.0f }),
    confidence(0.0f),
    label(PERSON) {
}

// Destructor
Object::~Object() {
    // Clean up if needed
}

// Getter implementations
std::string Object::getId() const {
    return unique_object_id;
}

std::vector<float> Object::getPosition() const {
    return position;
}

std::vector<float> Object::getVelocity() const {
    return velocity;
}

float Object::getConfidence() const {
    return confidence;
}

OBJECT_CLASS Object::getLabel() const {
    return label;
}

// Setter implementations
void Object::setId(const std::string& id) {
    unique_object_id = id;
}

void Object::setPosition(const std::vector<float>& pos) {
    position = pos;
}

void Object::setVelocity(const std::vector<float>& vel) {
    velocity = vel;
}

void Object::setConfidence(float conf) {
    confidence = conf;
}

void Object::setLabel(OBJECT_CLASS obj_class) {
    label = obj_class;
}